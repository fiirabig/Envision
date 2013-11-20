/*
 * ClassGenerator.h
 *
 *  Created on: Nov 13, 2013
 *      Author: marti
 */

#pragma once
#include "codeGeneration/CodeElementGenerator.h"
#include "codeGeneration/CodeGenerator.h"
#include "OOModel/src/allOOModelNodes.h"
#include "codeGeneration/CodeElement.h"

namespace JavaExport {

class ClassGenerator : public CodeElementGenerator {
public:
	ClassGenerator(Config config);
	virtual ~ClassGenerator();

	virtual CodeElement* generate(OOModel::Class* c) const ;
};

} /* namespace JavaExport */

