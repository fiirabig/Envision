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


#include "StatementPrinter.h"
#include "OOModel/src/allOOModelNodes.h"
using namespace OOModel;

namespace JavaExport {

StatementPrinter::StatementPrinter(SourcePrinter& printer,ExpressionPrinter* exprPrinter):
		printer_(printer),
		expressionPrinter_(exprPrinter){}

StatementPrinter::~StatementPrinter(){}

void StatementPrinter::print(OOModel::StatementItem* statement)
{
	printer_.startPrinting(statement);
	printStatement(statement);
	printer_.endPrinting(statement);
}

void StatementPrinter::printStatementItemList(OOModel::StatementItemList* list)
{
	printer_.startPrinting(list);
	printer_.print(" {");
	printer_.printNewLineAndIndent(SourcePrinter::IncrementIndent);
	for(auto item: *list) {
		print(item);
	}
	printer_.printNewLineAndIndent(SourcePrinter::DecrementIndent);
	printer_.print("}");
	printer_.endPrinting(list);
}

void StatementPrinter::printStatement(OOModel::StatementItem* statement)
{
	qDebug() << "printing statement " << statement->symbolName();
	bool verbose = true;

	if(auto block = dynamic_cast<Block*>(statement)) {
		if(verbose) qDebug() << "statement is Block";
		printStatementItemList(block->items());
		//TODO: wo chunt das for? nöd dassi denn en doppelblock kriege...
		Q_ASSERT(false && block);

	} else if(dynamic_cast<BreakStatement*>(statement)) {
		if(verbose) qDebug() << "statement is BreakStatement";
		printer_.print("break;");

	} else if(dynamic_cast<ContinueStatement*>(statement)) {
		if(verbose) qDebug() << "statement is ContinueStatement";
		printer_.print("continue;");

	} else if(auto declarationStatement = dynamic_cast<DeclarationStatement*>(statement)) {
		if(verbose) qDebug() << "statement is DeclarationStatement";
		//TODO
		Q_ASSERT(false && declarationStatement);

	} else if(auto expressionStatement = dynamic_cast<ExpressionStatement*>(statement)) {
		if(verbose) qDebug() << "statement is ExpressionStatement";
		expressionPrinter_->print(expressionStatement->expression());
		printer_.print(";");
		printer_.printNewLineAndIndent();

	} else if(auto forEachStatement = dynamic_cast<ForEachStatement*>(statement)) {
		if(verbose) qDebug() << "statement is ForEachStatement";
		//TODO:
		Q_ASSERT(false && forEachStatement);

	} else if(auto ifStatement = dynamic_cast<IfStatement*>(statement)) {
		if(verbose) qDebug() << "statement is IfStatement";
		printer_.print("if(");
		expressionPrinter_->print(ifStatement->condition());
		printer_.print(")");
		printStatementItemList(ifStatement->thenBranch());
		if(ifStatement->elseBranch()) {
			printer_.print(" else");
			printStatementItemList(ifStatement->elseBranch());
		}

	} else if(auto loopStatement = dynamic_cast<LoopStatement*>(statement)) {
		if(verbose) qDebug() << "statement is LoopStatement";
		printer_.print("for(");
		expressionPrinter_->print(loopStatement->initStep());
		printer_.print("; ");
		expressionPrinter_->print(loopStatement->condition());
		printer_.print("; ");
		expressionPrinter_->print(loopStatement->updateStep());
		printer_.print(")");
		printStatementItemList(loopStatement->body());

	} else if(auto returnStatement = dynamic_cast<ReturnStatement*>(statement)) {
		if(verbose) qDebug() << "statement is ReturnStatement";
		//TODO multiple return values?
		Q_ASSERT(false && returnStatement);

//	} else if(auto switchCase = dynamic_cast<SwitchCase*>(statement)) {
//		if(verbose) qDebug() << "statement is SwitchCase";
//		//TODO
//		Q_ASSERT(false && switchCase);

	} else if(auto switchStatement = dynamic_cast<SwitchStatement*>(statement)) {
		if(verbose) qDebug() << "statement is SwitchStatement";
		printer_.print("switch(");
		//expressionPrinter_->print(switchStatement->switchVar());
		printer_.print(") {");
		printer_.printNewLineAndIndent(SourcePrinter::IncrementIndent);
//		for(auto switchCase: *switchStatement->cases()) {
//			//print(switchCase);
//			qDebug() << "printing swichtCase" << switchCase;
//		}
		printer_.printNewLineAndIndent(SourcePrinter::DecrementIndent);
		printer_.print("}");
		printer_.printNewLineAndIndent();

		//TODO
		Q_ASSERT(false && switchStatement);

	} else if(auto tryCatchFinallyStatement = dynamic_cast<TryCatchFinallyStatement*>(statement)) {
		if(verbose) qDebug() << "statement is TryCatchFinallyStatement";
		//TODO
		Q_ASSERT(false && tryCatchFinallyStatement);

	} else
		Q_ASSERT(false && statement);
}
} /* namespace JavaExport */
