/***********************************************************************************************************************
 **
 ** Copyright (c) 2011, 2012 ETH Zurich
 ** All rights reserved.
 **
 ** Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
 ** following conditions are met:
 **
 **    * Redistributions of source code must retain the above copyright notice, this list of conditions and the
 **      following disclaimer.
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
 **********************************************************************************************************************/

#include "SourceToASTMap.h"
#include "SourcePrinter.h"
#include "ClassPrinter.h"
#include "ModulePrinter.h"
#include <QDir>

namespace JavaExport {

ModulePrinter::ModulePrinter()
{
	// TODO Auto-generated constructor stub

}

ModulePrinter::~ModulePrinter()
{
	// TODO Auto-generated destructor stub
}

void ModulePrinter::printModule(OOModel::Module* module, QString package, QString outputDir) {
	qDebug() << "printing module " << module->name() << " in package ";
	qDebug() << package << " in file " << outputDir << endl;
	/*
	ATTRIBUTE(Model::TypedList<Module>, modules, setModules)
	ATTRIBUTE(Model::TypedList<Class>, classes, setClasses)
	ATTRIBUTE(Model::TypedList<Method>, methods, setMethods)
	ATTRIBUTE(Model::TypedList<Field>, fields, setFields)
	*/
	for(auto nestedModule: *module->modules()) {
		//TODO: funktioniert das so?
		QString newPackage = package;
		newPackage.append(".");
		newPackage.append(module->name());
		QString newOutputDir = outputDir;
		QDir dir(outputDir);
		dir.mkdir(module->name());
		newOutputDir.append("/");
		newOutputDir.append(module->name());
		printModule(nestedModule,newPackage,newOutputDir);
	}

	if(module->classes()->size() > 0) {
		QDir dir(outputDir);
		if(!dir.exists()) dir.mkdir(outputDir);
		for(auto c: *module->classes()) {
			QString filename = outputDir;
			filename.append("/");
			filename.append(c->name());
			SourceToASTMap map(filename);
			SourcePrinter printer(filename, map);
			ExpressionPrinter* exprPrinter = new ExpressionPrinter(printer);
			ModifierPrinter* modPrinter= new ModifierPrinter(printer);
			StatementPrinter* stmtPrinter = new StatementPrinter(printer,exprPrinter);
			ClassPrinter classPrinter(printer,modPrinter,exprPrinter,stmtPrinter);
			classPrinter.print(c);
			delete exprPrinter;
			delete modPrinter;
			delete stmtPrinter;
		}
	}
}
} /* namespace JavaExport */
