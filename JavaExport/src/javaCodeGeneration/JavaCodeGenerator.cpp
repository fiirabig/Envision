/*
 * JavaCodeGenerator.cpp
 *
 *  Created on: Nov 14, 2013
 *      Author: marti
 */

#include "JavaCodeGenerator.h"
#include "codeGeneration/CodeElement.h"
#include "ModelBase/src/nodes/Node.h"
#include "OOModel/src/declarations/Declaration.h"
#include "OOModel/src/statements/Statement.h"
#include "OOModel/src/expressions/Expression.h"

namespace JavaExport
{

JavaCodeGenerator::JavaCodeGenerator()
{
	// TODO Auto-generated constructor stub
}

JavaCodeGenerator::~JavaCodeGenerator()
{
	// TODO Auto-generated destructor stub
}

//Todo: moved to JavaCodeElementGenerator
Scope* JavaCodeGenerator::curlyBraces(Model::Node* node) const
{
	return new Scope(node,curlyBracesLayout_);
}

Scope* JavaCodeGenerator::parenthesis(Model::Node* node) const
{
	return new Scope(node,parenthesisLayout_);
}

CodeElement* JavaCodeGenerator::generate(Model::Node* node) const
{
	if(auto declaration = dynamic_cast<OOModel::Declaration*>(node))
		return declarationGenerator_.generate(declaration);
	else if(auto statement = dynamic_cast<OOModel::Statement*>(node))
		return statementGenerator_.generate(statement);
	else if(auto expression = dynamic_cast<OOModel::Expression*>(node))
		return expressionGenerator_.generate(expression);
	else return elementGenerator_.generate(node);

//	qDebug() << "unimplemented " << node->symbolName();
//	Q_ASSERT(false &&  "unimplemented");
//	return nullptr;

}

} /* namespace JavaExport */
