/*
 * JavaCodeGenerator.cpp
 *
 *  Created on: Nov 14, 2013
 *      Author: marti
 */

#include "JavaCodeGenerator.h"
#include "JavaConfig.h"
#include "codeGeneration/CodeElement.h"
#include "ModelBase/src/nodes/Node.h"
#include "OOModel/src/declarations/Declaration.h"
#include "OOModel/src/elements/StatementItem.h"
#include "OOModel/src/expressions/Expression.h"

namespace JavaExport
{

JavaCodeGenerator::JavaCodeGenerator() : CodeGenerator(javaConfig())
{
	// TODO Auto-generated constructor stub
}

JavaCodeGenerator::~JavaCodeGenerator()
{
	// TODO Auto-generated destructor stub
}

CodeElement* JavaCodeGenerator::generate(Model::Node* node) const
{
	if(!node) return nullptr;
	//TODO: ask mitko
	if(auto declaration = dynamic_cast<OOModel::Declaration*>(node))
		return declarationGenerator_.DeclarationGenerator::generate(declaration);
	else if(auto statement = dynamic_cast<OOModel::StatementItem*>(node))
		return statementGenerator_.StatementItemGenerator::generate(statement);
	else if(auto expression = dynamic_cast<OOModel::Expression*>(node))
		return expressionGenerator_.generate(expression);
	else return elementGenerator_.ElementGenerator::generate(node);

//	qDebug() << "unimplemented " << node->symbolName();
//	Q_ASSERT(false &&  "unimplemented");
//	return nullptr;

}

} /* namespace JavaExport */
