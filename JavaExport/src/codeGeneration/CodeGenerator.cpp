/*
 * CodeGenerator.cpp
 *
 *  Created on: Nov 13, 2013
 *      Author: marti
 */

#include "CodeGenerator.h"
#include "LayoutConfig.h"
#include "CodeElement.h"
#include "OOModel/src/declarations/Declaration.h"
#include "OOModel/src/statements/Statement.h"
#include "OOModel/src/expressions/Expression.h"
#include "ModelBase/src/nodes/Node.h"
#include "ModelBase/src/nodes/TypedList.h"

#include <QDir>


namespace JavaExport
{

CodeGenerator::CodeGenerator(Config config): config_(config)
{

}

CodeGenerator::~CodeGenerator()
{
	// TODO Auto-generated destructor stub
}

bool CodeGenerator::removeDir(const QString& dirName)
{
	bool result = false;
	QDir dir(dirName);
	if (dir.exists()) {
		Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
			if (info.isDir()) {
				result = removeDir(info.absoluteFilePath());
			}
			else {
				result = QFile::remove(info.absoluteFilePath());
			}

			if (!result) {
				return false;
			}
		}
		result = dir.rmdir(dir.absolutePath());
	}
	return result;
}


void CodeGenerator::printSourceFiles(Model::Node* root, const QString outputDirectory)
{
	qDebug() << "starting to printing sourceFiles from " << root << " into " << outputDirectory;

	removeDir(outputDirectory);

	auto parent = new SourceDirectory(nullptr,"");

	auto output = new SourceDirectory(nullptr,outputDirectory);
	output->setParentDirectory(parent);
	*output << root;

	print(output);
	delete parent;
}

CodeElement* CodeGenerator::print(CodeElement* element)
{
	Q_ASSERT(element->parentDirectory() && "element has no parent directory");
	//TODO: report
	qDebug() << "\nstarting to print element" << element->toString();

	if(auto sourceDir = dynamic_cast<SourceDirectory*>(element))
	{
		qDebug() << "\tprinting SourceDirectory " << sourceDir->toString();

		QString path = sourceDir->parentDirectory()->qDir().absolutePath();
		if(!sourceDir->name().isEmpty())
		{
			path +=  "/" + sourceDir->name();
			sourceDir->qDir().mkdir(path);
		}
		sourceDir->setPath(path);

		qDebug() << "\tfinished printing sourceDirectory " << sourceDir->toString() << "\n";

	}
	else if(auto file = dynamic_cast<SourceFile*>(element))
	{
		qDebug()<< "\tprinting SourceFile " << file->toString();

		auto fc = new FileController(config(),file);
		file->setFileController(fc);

		qDebug() << "\tfinished printing SourceFile " << file->toString();
	}

	else if(auto scope = dynamic_cast<Scope*>(element))
	{
		qDebug() << "\tprinting scope" << scope->toString() << flush;

		scope->content().prepend(new OpenScope(scope->owner(),scope->scopeLayout()));
		scope->content().append(new CloseScope(scope->owner(),scope->scopeLayout()));

		qDebug() << "\tfinished printing scope" << scope->toString() << flush;
	}

	else if(auto snippet = dynamic_cast<SourceCodeSnippet*>(element))
	{
		qDebug() << "\tprinting snippet" << snippet->toString() << flush;

		Q_ASSERT(snippet->sourceFile() && "CodeSnippet has no SourceFile");
		Q_ASSERT(snippet->sourceFile()->fileController() && "SourceFile has no FileController");

		snippet->sourceFile()->fileController()->print(snippet->text());
		map(snippet->sourceFile()->fileController()->cursor(), snippet->owner());

		qDebug() << "\tfinished printing snippet" << snippet->toString() << "\n";

		delete snippet;
		return nullptr;
	}

	else if(auto openScope = dynamic_cast<OpenScope*>(element)) {

		qDebug() << "\tprinting openScope";

		openScope->sourceFile()->fileController()->openScope(openScope->scopeLayout());
		map(openScope->sourceFile()->fileController()->cursor(),openScope->owner());

		qDebug() << "\tfinished printing openScope";

		delete openScope;
		return nullptr;
	}

	else if(auto closeScope = dynamic_cast<CloseScope*>(element))
	{
		qDebug() << "\tprinting closeScope";

		closeScope->sourceFile()->fileController()->closeScope(closeScope->scopeLayout());
		map(closeScope->sourceFile()->fileController()->cursor(),closeScope->owner());

		qDebug() << "\tfinished printing closeScope";

		delete closeScope;
		return nullptr;
	}

	else if(auto newLine = dynamic_cast<NewLine*>(element)) {

		qDebug() << "\tprinting newLine";

		newLine->sourceFile()->fileController()->printNewLine();
		map(newLine->sourceFile()->fileController()->cursor(),newLine->owner());

		qDebug() << "\tfinished printing newLine";

		delete newLine;
		return nullptr;
	}

	else if(auto package = dynamic_cast<Package*>(element)) {

		qDebug() << "\tprinting package";

		//TODO:
		Q_ASSERT(false && "not implemented package");
		map(package->sourceFile()->fileController()->cursor(),package->owner());

		qDebug() << "\tfinished printing package";

		delete package;
		return nullptr;
	}

	else if(auto ignore = dynamic_cast<Ignore*>(element)) {

		qDebug() << "\tprinting ignore";

		//TODO:
		//Q_ASSERT(false && "not implemented ignore");

		qDebug() << "\tfinished printing ignore";

		delete ignore;
		return nullptr;
	}

	else if(auto error = dynamic_cast<Error*>(element)) {

		qDebug() << "\tprinting error" << error->toString();

		//TODO:
		qDebug() << error->message();
		Q_ASSERT(false && "not implemented error");

		qDebug() << "\tfinished printing error";

		delete error;
		return nullptr;
	}


	if(auto container = dynamic_cast<CodeElementContainer*>(element))
	{
		qDebug()  << "\tprinting container content" << container->toString();

		while(!container->content().isEmpty())
		{
			auto next = container->content().takeFirst();
		//	qDebug() << "\t\tcontainer is " << container->toString();
		//	qDebug() << "\t\ttaking first element from container and initializing it" << next->toString();

			if(!next->parentDirectory())
			{
				if(auto dir = dynamic_cast<SourceDirectory*>(container))
					next->setParentDirectory(dir);
				else
					next->setParentDirectory(container->parentDirectory());
				//qDebug() << "\t\ŧset parentDirectory of";
			}

			if(!next->sourceFile())
			{
				if(auto file = dynamic_cast<SourceFile*>(container))
				{
					//qDebug() << "container is  sourcefile " << container->toString();
					//qDebug() << "setting sourcefile to container...";
					next->setSourceFile(file);
					//qDebug() << "source file of " << next->toString() << "is now " << next->sourceFile()->toString();
				}

				else next->setSourceFile(container->sourceFile());
				//qDebug() << "\t\tset parentDirectory of";
			}

			//qDebug() << "finished initializing " << next->toString() << flush;

			if(auto printed = print(next))
			{
				container->content().prepend(printed);
				qDebug() << "\t\tadded "<< printed->toString() << " to container" << container->toString();
			}
		}
		qDebug() << "\tfinished printing container" << container->toString() << "\n" << flush;

		Q_ASSERT(container->content().isEmpty());
		delete container;
		return nullptr;
	}

	qDebug() << "\tgenerating element" << element->toString() << flush;
	return generate(element->owner());

}

void CodeGenerator::map(FileController::Cursor cursor, Model::Node* node)
{
	qDebug() << "mapping" << node << &cursor;
}


} /* namespace JavaExport */


