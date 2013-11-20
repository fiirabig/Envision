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

#include "JavaStatementItemGenerator.h"
#include "JavaConfig.h"

#include "OOModel/src/elements/StatementItem.h"
#include "OOModel/src/statements/Block.h"
#include "OOModel/src/statements/BreakStatement.h"
#include "OOModel/src/statements/ContinueStatement.h"
#include "OOModel/src/statements/DeclarationStatement.h"
#include "OOModel/src/statements/ExpressionStatement.h"
#include "OOModel/src/statements/ForEachStatement.h"
#include "OOModel/src/statements/IfStatement.h"
#include "OOModel/src/statements/LoopStatement.h"
#include "OOModel/src/statements/ReturnStatement.h"
#include "OOModel/src/statements/Statement.h"
#include "OOModel/src/statements/SwitchStatement.h"
#include "OOModel/src/statements/TryCatchFinallyStatement.h"

namespace JavaExport {

JavaStatementItemGenerator::JavaStatementItemGenerator() :
		StatementItemGenerator(javaConfig())
{
	// TODO Auto-generated constructor stub
}

JavaStatementItemGenerator::~JavaStatementItemGenerator()
{
	// TODO Auto-generated destructor stub
}

CodeElement* JavaStatementItemGenerator::generate(OOModel::Block* statement) const
{
	//TODO: ask mitko
	return curlyBraces(statement,statement->items());
}


CodeElement* JavaStatementItemGenerator::generate(OOModel::BreakStatement* statement) const
{
	auto code = new Code(statement);
	*code << "break;" << new NewLine(statement);
	return code;
}


CodeElement* JavaStatementItemGenerator::generate(OOModel::ContinueStatement* statement) const
{
	auto code = new Code(statement);
	*code << "continue;" << new NewLine(statement);
	return code;
}


CodeElement* JavaStatementItemGenerator::generate(OOModel::DeclarationStatement* decl) const
{
	//TODO: ask Mitko about ; newline
	auto code = new Code(decl);
	*code << decl->declaration() << ";" <<  new NewLine(decl);
	return code;
}


CodeElement* JavaStatementItemGenerator::generate(OOModel::ExpressionStatement* expr) const
{
	//TODO: ask Mitko about ; newline
//	return new CodeElement(expr->expression());
	auto code = new Code(expr);
	*code << expr->expression() << ";" <<  new NewLine(expr);
	return code;
}



CodeElement* JavaStatementItemGenerator::generate(OOModel::ForEachStatement* forEach) const
{
	//TODO: ask Mitko about custom return
	auto code = new Code(forEach);
	*code << "for(" << forEach->varType() << " " << forEach->varName() << " : "
		  << forEach->collection() << ")" << forEach->body();
	return code;
}



CodeElement* JavaStatementItemGenerator::generate(OOModel::IfStatement* ifstmt) const
{
	auto code = new Code(ifstmt);
	*code << "if(" << ifstmt->condition() << ")" << ifstmt->thenBranch();
	if(ifstmt->elseBranch()) *code << "else" << ifstmt->elseBranch();
	return code;
}


CodeElement* JavaStatementItemGenerator::generate(OOModel::LoopStatement* loop) const
{
	//TODO: check if the ; are right && make sure to test empty init and update
	auto code = new Code(loop);
	*code << "for(" << loop->initStep() << ";" << loop->condition() << ";"
		  << loop->updateStep() << ")" << loop->body();
	return code;
}



CodeElement* JavaStatementItemGenerator::generate(OOModel::ReturnStatement* returnStmt) const
{
	auto code = new Code(returnStmt);
	if(returnStmt->values()->size()>1)
		*code << new NotAllowed(returnStmt->values(), "In Java return can have only one Expression");
	else
		*code << "return " << returnStmt->values() << ";";
	return code;
}

CodeElement* JavaStatementItemGenerator::generate(OOModel::Statement* statement) const
{
	return unimplemented(statement);
}


CodeElement* JavaStatementItemGenerator::generate(OOModel::SwitchStatement* switchStmt) const
{
	//TODO: test, dont forget with and without default
	auto code = new Code(switchStmt);
	*code << "switch" << parenthesis(switchStmt, switchStmt->switchVar())
		  << curlyBraces(switchStmt,switchStmt->cases());
	return code;
}

CodeElement* JavaStatementItemGenerator::generate(OOModel::TryCatchFinallyStatement* stmt) const
{
	//todo: test, with/without finally, one or more catchClause...
	auto code = new Code(stmt);
	*code << "try" << stmt->tryBody() << stmt->catchClauses() << "finally" << stmt->finallyBody();
	return code;
}

} /* namespace JavaExport */
