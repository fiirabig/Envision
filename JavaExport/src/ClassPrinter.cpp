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



#include "ClassPrinter.h"

namespace JavaExport {

ClassPrinter::ClassPrinter(SourcePrinter& printer,
		ModifierPrinter* modPrinter, ExpressionPrinter* exprPrinter,
		StatementPrinter* statementPrinter)
:
		printer_(printer),
		modifierPrinter_(modPrinter),
		expressionPrinter_(exprPrinter),
		statementPrinter_(statementPrinter)

{
		//modifierPrinter_ = new ModifierPrinter(printer);
		//expressionPrinter_ = new ExpressionPrinter(printer);
}

ClassPrinter::~ClassPrinter()
{
	//delete modifierPrinter_;
	//delete expressionPrinter_;
}

void ClassPrinter::print(OOModel::Class* c)
{
	printer_.startPrinting(c);
	printClass(c);
	printer_.endPrinting(c);
}

void ClassPrinter::printClass(OOModel::Class* c) {
	qDebug() << "printing class " << c->name();

	/*From Declaration
	ATTRIBUTE_OOP_NAME
	- ATTRIBUTE(Modifier, modifiers, setModifiers)
	ATTRIBUTE_OOP_ANNOTATIONS
	ATTRIBUTE(Model::TypedList<Declaration>, subDeclarations, setSubDeclarations)
	 */
	/*
	- ATTRIBUTE(Model::TypedList<Expression>, baseClasses, setBaseClasses)
	ATTRIBUTE(Model::TypedList<Expression>, friends, setFriends)
	- ATTRIBUTE(Model::TypedList<FormalTypeArgument>, typeArguments, setTypeArguments)
	ATTRIBUTE(Model::TypedList<Class>, classes, setClasses)
	ATTRIBUTE(Model::TypedList<Method>, methods, setMethods)
	ATTRIBUTE(Model::TypedList<Field>, fields, setFields)
	ATTRIBUTE(Model::TypedList<Enumerator>, enumerators, setEnumerators)
	*/
	printClassHeader(c);
	printClassBody(c);
}

void ClassPrinter::printClassHeader(OOModel::Class* c)
{
	modifierPrinter_->print(c->modifiers());
	printer_.print("class ");
	printer_.print(c->name());
	//TODO: move to print class Body
}

void ClassPrinter::printTypeArguments(Model::TypedList<OOModel::FormalTypeArgument>* args)
{
	//TODO: need to add them to the map??
	bool first = true;
	if(args && args->size() >0) {
		printer_.print("<");
		for(auto arg : *args) {
			if(!first) {
				printer_.print(", ");
			}
			first = false;
			printer_.print(arg->name());
			//TODO: stimmt das ->> test!!
			if(auto subtype = arg->subTypeOfExpression()){
				printer_.print(" extends ");
				printer_.print( subtype->symbolName());
			}
			//TODO: stimmt das ->> test!!
			if(auto superType = arg->superTypeOfExpression()) {
				printer_.print(" super ");
				printer_.print(superType->symbolName());
			}
		}
		printer_.print("> ");
		//TODO: fehlt da en abstand?
	}
}

void ClassPrinter::printBaseClasses(OOModel::Class* c)
{
	auto baseClasses = c->baseClasses();
	if( baseClasses && (baseClasses -> size() > 0)){
	//TODO: could simulate multiple inheritance with interfaces and
	// members of the additional baseclasses?
	Q_ASSERT(baseClasses->size() == 1);
	printer_.print(" extends ");

	//todo printType(baseClasses -> first()->type());
	}
}

void ClassPrinter::printClassBody(OOModel::Class* c)
{
	printer_.print(" {");
	printer_.printNewLineAndIndent(SourcePrinter::IncrementIndent);
	printFields(c);
	printMethods(c);
	//TODO: nested classes & enums
	printer_.printNewLineAndIndent(SourcePrinter::DecrementIndent);
	printer_.print("}");
	printer_.printNewLineAndIndent();
}
void ClassPrinter::printFields(OOModel::Class* c)
{
	qDebug() << c->name() << ": printing fields...";
	for(auto field: *c->fields()) {
		printer_.startPrinting(field);
		expressionPrinter_->printVariableDeclaration(field);
		printer_.print(";");
		printer_.endPrinting(field);
		printer_.printNewLineAndIndent();
	}
}
void ClassPrinter::printMethods(OOModel::Class* c)
{
	qDebug() << c->name() << ": printing methods...";

//		ATTRIBUTE(StatementItemList, items, setItems)
//		ATTRIBUTE(Model::TypedList<FormalTypeArgument>, typeArguments, setTypeArguments)
//		ATTRIBUTE(Model::TypedList<FormalArgument>, arguments, setArguments)
//		ATTRIBUTE(Model::TypedList<FormalResult>, results, setResults)
//		ATTRIBUTE(Model::TypedList<MemberInitializer>, memberInitializers, setMemberInitializers)
//		PRIVATE_ATTRIBUTE_VALUE(Model::Integer, mthKind, setMthKind, int)

	for(OOModel::Method* method: *c->methods()) {
		printer_.printNewLineAndIndent();
		printer_.startPrinting(method);
		printMethodHeader(method);
		printMethodBody(method);
		printer_.endPrinting(method);
		printer_.printNewLineAndIndent();
	}

}
void ClassPrinter::printMethodHeader(OOModel::Method* method)
{
	modifierPrinter_->print(method->modifiers());
	//TODO: print type args
	Q_ASSERT(method->typeArguments()->size()==0);
	auto results = method->results();
	//TODO: multiple result types??
	Q_ASSERT(results && results->size() == 1);
	expressionPrinter_->print(results->first()->typeExpression());
	printer_.print(" ");
	printer_.print(method->name());
	printer_.print("(");
	bool first = true;
	for(auto arg: *method->arguments()) {
		if(!first) printer_.print(" ,");
		first = false;
		//TODO: formal arg has direction?
		expressionPrinter_->print(arg->typeExpression());
		printer_.print(" ");
		printer_.print(arg->name());
	}
	printer_.print(")");

}
void ClassPrinter::printMethodBody(OOModel::Method* method)
{
	statementPrinter_->printStatementItemList(method->items());
	//todo replace with statmentPrinter::printStatementItemList
//	printer_.print(" {");
//	printer_.printNewLineAndIndent(SourcePrinter::IncrementIndent);
//	printer_.startPrinting(method->items());
//	for(auto item: *method->items()) {
//		statementPrinter_->print(item);
//	}
//	printer_.endPrinting(method->items());
//	printer_.printNewLineAndIndent(SourcePrinter::DecrementIndent);
//	printer_.print("}");
}

} /* namespace JavaExport */
