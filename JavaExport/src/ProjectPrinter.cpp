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



#include "ProjectPrinter.h"
#include "ModulePrinter.h"
#include <QDir>
namespace JavaExport {

//Todo: remove printer from constr
ProjectPrinter::ProjectPrinter(){}

ProjectPrinter::~ProjectPrinter() {}

//TODO: give outputDir a default value?
void ProjectPrinter::printProject(OOModel::Project* project, QString package, QString outputDir) {
	qDebug() << "printing  project " << project <<  outputDir << package <<endl;
	/*
	ATTRIBUTE(Model::TypedList<Project>, projects, setProjects)
	ATTRIBUTE(Model::TypedList<Module>, modules, setModules)
	ATTRIBUTE(Model::TypedList<Class>, classes, setClasses)
	ATTRIBUTE(Model::TypedList<Method>, methods, setMethods)
	ATTRIBUTE(Model::TypedList<Field>, fields, setFields)
	 */

	// TODO: print projects -> ?? packages
	// TODO: print Modules -> ?? packages
	// TODO: print classes
	// TODO: print methods -> ??
	// TODO: print fields -> ??

	qDebug() << "projects :" << endl;
	for(auto element:*project->projects()) {
		qDebug() << "    " << element->name() << endl;
	}
	qDebug() << "modules :" << endl;
	for(auto element:*project->modules()) {
		qDebug() << "    " << element->name() << endl;
	}
	qDebug() << "classes :" << endl;
	for(auto element:*project->classes()) {
		qDebug() << "    " << element->name() << endl;
	}
	qDebug() << "methods :" << endl;
	for(auto element:*project->methods()) {
		qDebug() << "    " << element->name() << endl;
	}
	qDebug() << "fields :" << endl;
	for(auto element:*project->fields()) {
		qDebug() << "    " << element->name() << endl;
	}

	for(auto nestedProject:*project->projects()) {
		//TODO: funktioniert das so?
		QString newPackage = package;
		newPackage.append(".");
		newPackage.append(nestedProject->name());
		QString newOutputDir = outputDir;
		QDir dir(outputDir);
		dir.mkdir(nestedProject->name());
		newOutputDir.append("/");
		newOutputDir.append(nestedProject->name());
		printProject(nestedProject,newPackage,newOutputDir);
	}


	if(project->modules()->size() > 0){
		ModulePrinter modulePrinter;
		for(auto module:*project->modules()) {
			//TODO: funktioniert das so?
			QString newPackage = package;
			newPackage.append(".");
			newPackage.append(module->name());
			QString newOutputDir = outputDir;
			QDir dir(outputDir);
			dir.mkdir(module->name());
			newOutputDir.append("/");
			newOutputDir.append(module->name());
			modulePrinter.printModule(module,newPackage,newOutputDir);
		}
	}
}

} /* namespace JavaExport */
