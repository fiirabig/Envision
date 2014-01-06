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
#include "OOModel/src/declarations/Project.h"




namespace JavaExport
{

CodeGenerator::CodeGenerator(Config config): config_(config)
{

}

CodeGenerator::~CodeGenerator()
{
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

	if(auto sourceDir = dynamic_cast<SourceDirectory*>(element))
	{
		QString path = sourceDir->parentDirectory()->qDir().absolutePath();
		if(!sourceDir->name().isEmpty())
		{
			path +=  "/" + sourceDir->name();
			sourceDir->qDir().mkdir(path);
		}
		sourceDir->setPath(path);
	}
	else if(auto file = dynamic_cast<SourceFile*>(element))
	{
		auto fc = new FileController(config(),file);
		file->setFileController(fc);
	}

	else if(auto scope = dynamic_cast<Scope*>(element))
	{
		scope->content().prepend(new OpenScope(scope->owner(),scope->scopeLayout()));
		scope->content().append(new CloseScope(scope->owner(),scope->scopeLayout()));
	}

	else if(auto snippet = dynamic_cast<SourceCodeSnippet*>(element))
	{
		Q_ASSERT(snippet->sourceFile() && "CodeSnippet has no SourceFile");
		Q_ASSERT(snippet->sourceFile()->fileController() && "SourceFile has no FileController");

		snippet->sourceFile()->fileController()->print(snippet->text());
		map(element);

		delete snippet;
		return nullptr;
	}

	else if(auto openScope = dynamic_cast<OpenScope*>(element)) {

		openScope->sourceFile()->fileController()->openScope(openScope->scopeLayout());
		map(element);

		delete openScope;
		return nullptr;
	}

	else if(auto closeScope = dynamic_cast<CloseScope*>(element))
	{

		closeScope->sourceFile()->fileController()->closeScope(closeScope->scopeLayout());
		map(element);

		delete closeScope;
		return nullptr;
	}

	else if(auto newLine = dynamic_cast<NewLine*>(element)) {

		newLine->sourceFile()->fileController()->printNewLine();
		map(element);

		delete newLine;
		return nullptr;
	}

	else if(auto package = dynamic_cast<Package*>(element)) {

		QString packageString;
		bool first = true;
		auto parent = package->parentDirectory();
		while(parent && parent->owner() && !dynamic_cast<OOModel::Project*>(parent->owner()) )
		{
			bool emptyName = parent->name().isEmpty();
			if(first && !emptyName) first = false;
			else if(!emptyName) packageString.prepend(".");
			packageString.prepend(parent->name());
			parent = parent->parentDirectory();
		}

		if(!packageString.isEmpty())
		{
			package->sourceFile()->fileController()->print("package " + packageString);
			package->sourceFile()->fileController()->printNewLine();
			package->sourceFile()->fileController()->printNewLine();
		}

		map(element);

		delete package;
		return nullptr;
	}

	else if(auto ignore = dynamic_cast<Ignore*>(element)) {

		delete ignore;
		return nullptr;
	}

	else if(auto error = dynamic_cast<Error*>(element)) {

		delete error;
		return nullptr;
	}


	if(auto container = dynamic_cast<CodeElementContainer*>(element))
	{
		while(!container->content().isEmpty())
		{
			auto next = container->content().takeFirst();

			if(!next->parentDirectory())
			{
				if(auto dir = dynamic_cast<SourceDirectory*>(container))
					next->setParentDirectory(dir);
				else
					next->setParentDirectory(container->parentDirectory());
			}

			if(!next->sourceFile())
			{
				if(auto file = dynamic_cast<SourceFile*>(container))
				{
					next->setSourceFile(file);
				}

				else next->setSourceFile(container->sourceFile());
			}

			if(auto printed = print(next))
			{
				container->content().prepend(printed);
			}
		}

		Q_ASSERT(container->content().isEmpty());
		delete container;
		return nullptr;
	}

	return generate(element->owner());

}


void CodeGenerator::map(CodeElement* element) {
	map_.add(element);
}

} /* namespace JavaExport */


