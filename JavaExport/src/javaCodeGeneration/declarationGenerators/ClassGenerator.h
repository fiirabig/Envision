/*
 * ClassGenerator.h
 *
 *  Created on: Nov 13, 2013
 *      Author: marti
 */

#pragma once
#include "javaCodeGeneration/JavaCodeElementGenerator.h"
#include "codeGeneration/CodeGenerator.h"
#include "OOModel/src/allOOModelNodes.h"
#include "codeGeneration/CodeElement.h"

namespace JavaExport {

class ClassGenerator : public JavaCodeElementGenerator {
public:
	ClassGenerator();
	virtual ~ClassGenerator();

	virtual CodeElement* generate(OOModel::Class* c) const ;
};

} /* namespace JavaExport */

