/***********************************************************************************************************************
 **
 ** Copyright (c) 2011, 2013 ETH Zurich
 ** All rights reserved.
 **
 ** Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
 ** following conditions are met:
 **
 **    * Redistributions of source code must retain the above copyright notice, this list of conditions and the following
 **      disclaimer.
 **    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 **      following disclaimer in the documentation and/or other materials provided with the distribution.
 **    * Neither the name of the ETH Zurich nor the names of its contributors may be used to endorse or promote products
 **      derived from this software without specific prior written permission.
 **
 **
 ** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 ** INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 ** DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 ** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 ** SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 ** WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 ** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 **
 ***********************************************************************************************************************/

#include "CodeGenerator.h"
#include "Config.h"
#include "CodeElement.h"
#include "OOModel/src/declarations/Declaration.h"
#include "OOModel/src/statements/Statement.h"
#include "OOModel/src/expressions/Expression.h"
#include "ModelBase/src/nodes/Node.h"
#include "ModelBase/src/nodes/TypedList.h"




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
		for(QFileInfo info : dir.entryInfoList(QDir::NoDotAndDotDot| QDir::AllDirs |
				QDir::Files, QDir::DirsFirst))
		{
			if (info.isDir())
			{
				result = removeDir(info.absoluteFilePath());
			}
			else
			{
				result = QFile::remove(info.absoluteFilePath());
			}

			if (!result)
			{
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

	auto parent = SourceDirectory(nullptr,"");

	auto output = new SourceDirectory(nullptr,outputDirectory);
	output->setParentDirectory(&parent);
	*output << root;

	print(output);
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


