/***********************************************************************************************************************
 **
 ** Copyright (c) 2011, 2013 ETH Zurich
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


#include "SourceBuilder.h"
#include "OOModel/src/allOOModelNodes.h"
#include "OOModel/src/types/ArrayType.h"
#include "OOModel/src/types/ClassType.h"
#include "OOModel/src/types/ErrorType.h"
#include "OOModel/src/types/LambdaType.h"
#include "OOModel/src/types/NullType.h"
#include "OOModel/src/types/PointerType.h"
#include "OOModel/src/types/PrimitiveType.h"
#include "OOModel/src/types/ReferenceType.h"
#include "OOModel/src/types/StringType.h"
#include "OOModel/src/types/SymbolProviderType.h"
#include "OOModel/src/types/ThrownExceptionType.h"

using namespace OOModel;
using namespace std;

namespace JavaExport {

SourceBuilder::SourceBuilder(string filename, int indentation)
: indent_{indentation}
{
	dest_.open(filename);
}


void SourceBuilder::printIndent(){
	for(int i = 0; i < indent_; i++){
		dest_ << "    ";
		//TODO: have this configurable??;
	}
}

SourceBuilder::~SourceBuilder() {
	dest_.close();
}

void SourceBuilder::createSourceFromClass(Class* c) {
	//TODO: remove debug output
	cout << "#############################################################################";
	//indent <visibility> class <classname> <generic args> (extends <baseclassname>) {\n

	printClassHeader(c);
	lines_.push_back(c);
	//TODO: remove debug output
	cout << "\nprinted header\n";
	indent_++;

	//for(auto element:*c->fields())
	for(auto it = c->fields()->begin(); it!= c->fields()->end(); it++){
		printFieldDeclaration(*it);
		lines_.push_back(*it);
	}
    //TODO: remove
	cout << "lines contains " << lines_.size() << " entries";

	indent_--;
	printIndent();
	dest_ << "}" << endl;
	//TODO: make a closing bracket node?
	lines_.push_back(nullptr);

}

void SourceBuilder::printClassHeader(Class* c) {
/*
ClassDeclaration:
	NormalClassDeclaration
	EnumDeclaration

NormalClassDeclaration:
	ClassModifiers(opt) "class" Identifier TypeParameters(opt)
							Super(opt)	Interfaces(opt)	ClassBody

-> page 208
ClassModifiers:
	ClassModifier
	ClassModifiers ClassModifier

ClassModifier: one of
	Annotation
	public
	protected
	private
	abstract
	static
	final
	strictfp
*/

	//TODO: remove debug output
	cout << "\nentered printClassHeader";
	printIndent();
	printVisibility(c -> visibility());
	dest_ << " class " << c->name().toStdString();

	printFormalTypeArguments(c->typeArguments());
   cout << "blas";

	auto baseClasses = c->baseClasses();
	if( baseClasses && (baseClasses -> size() > 0)){
		//TODO: what about more than one baseClass?
		Q_ASSERT(baseClasses->size() == 1);
		dest_ << " extends " ;
		printType(baseClasses -> first()->type());
	}
	dest_ << " {\n";

}


void SourceBuilder::printFormalTypeArguments(Model::TypedList<FormalTypeArgument>* args){
  if(args && args->size()>0){
	  dest_ << "<";
	  for(auto it = args->begin(); it != args->end(); ++it) {
		  if(*it) {
			  if(it != args->begin()) dest_ << ", ";
			  dest_ << (*it)->name().toStdString();
			  if(auto subtype = (*it)->subTypeOfExpression()){
				  dest_ << " extends " << subtype->symbolName().toStdString();
				  //TODO: what kinds of expressions can I expect here? is symbolName ok?
				  //TODO: what about interfaces?
			  }
			  if(auto superType = (*it)->superTypeOfExpression()) {
				  dest_ << " super " << superType->symbolName().toStdString();
			  }
		  }
	  }
	  dest_ << ">";
  }
}


void SourceBuilder::printType(const Type* type) {
	cout << "entered printType" << endl << flush;
	//TODO:remove output

	const ArrayType* arrayType  = dynamic_cast<const ArrayType*>(type);
	if (arrayType){
		printType(arrayType->elementType());
		dest_ << "[]";
		return;
	}
	const ClassType* classType  = dynamic_cast<const ClassType*>(type);
	if (classType){
		cout << "printing classType" << classType << endl << flush;
		dest_ << classType -> classDefinition()->name().toStdString();
		return;
	}
	const ErrorType* errorType  = dynamic_cast<const ErrorType*>(type);
	if (errorType){
		//TODO: what comes here?
		cout << "printing errorType " << errorType << endl;
		return;
	}

	const LambdaType* lambdaType  = dynamic_cast<const LambdaType*>(type);
	if (lambdaType){
		//TODO: what comes here?
		cout << "printing lambdaType " << lambdaType << endl;
		return;
	}
	const NullType* nullType  = dynamic_cast<const NullType*>(type);
	if (nullType){
		//XXX: Null type has no name...
		// there never should be the need to print it.
		//http://stackoverflow.com/questions/2707322/what-is-null-in-java
		cout << "printing nullType " << nullType << endl;
		Q_ASSERT(false && "trying to print NullType");
		return;
	}
	const PointerType* pointerType  = dynamic_cast<const PointerType*>(type);
	if (pointerType){
		//XXX: there is no Pointer type in java
		cout << "printing pointerType " << pointerType << endl;
		Q_ASSERT(false && "trying to print PointerType");
		return;
	}
	const PrimitiveType* primitiveType  = dynamic_cast<const PrimitiveType*>(type);
	if (primitiveType){
		printPrimitiveType(primitiveType->type());
		cout << "printing primitiveType " << primitiveType << endl;
		return;
	}
	const ReferenceType* referenceType  = dynamic_cast<const ReferenceType*>(type);
	if (referenceType){
		//TODO: what does reference type mean in the context of java?
		printType(referenceType->baseType());
		cout << "printing referenceType " << referenceType << endl;
		return;
	}
	const StringType* stringType  = dynamic_cast<const StringType*>(type);
	if (stringType){
		dest_ << "String";
		cout << "printing stringType " << stringType << endl;
		return;
	}
	const SymbolProviderType* symbolProviderType  = dynamic_cast<const SymbolProviderType*>(type);
	if (symbolProviderType){
		//TODO: what comes here?
		cout << "printing symbolProviderType " << symbolProviderType << endl;
		return;
	}
	const ThrownExceptionType* thrownExceptionType  = dynamic_cast<const ThrownExceptionType*>(type);
	if (thrownExceptionType){
		//TODO: what comes here?
		printType(thrownExceptionType->exceptionType());
		cout << "printing thrownExceptionType " << thrownExceptionType << endl;
		return;
	}
	Q_ASSERT(false&&"trying to print an unknown type");
}

void SourceBuilder::printPrimitiveType(PrimitiveType::PrimitiveTypes type) {
	//enum PrimitiveTypes {INT, LONG, UNSIGNED_INT, UNSIGNED_LONG,FLOAT, DOUBLE, BOOLEAN, CHAR, VOID};
	//TODO: missing types: byte, short, long
	switch (type)
	{
	case PrimitiveType::PrimitiveType::INT:  {dest_ << "int";return;}
	case PrimitiveType::PrimitiveType::LONG:  {dest_ << "long";return;}
	case PrimitiveType::PrimitiveType::FLOAT:  {dest_ << "float";return;}
	case PrimitiveType::PrimitiveType::DOUBLE:  {dest_ << "double";return;}
	case PrimitiveType::PrimitiveType::BOOLEAN:  {dest_ << "boolean";return;}
	case PrimitiveType::PrimitiveType::CHAR:  {dest_ << "char";return;}
	case PrimitiveType::PrimitiveType::VOID:  {dest_ << "void";return;}
	//TODO: Types that don't appear in java
	case PrimitiveType::PrimitiveType::UNSIGNED_INT:
	case PrimitiveType::PrimitiveType::UNSIGNED_LONG:  {
		Q_ASSERT(false&&"trying to print a primitive type that doesn't exist in java");
		return;
	}
	default: Q_ASSERT(false && "trying to print a bad primitivetypes enum");
	}
}

void SourceBuilder::printFieldDeclaration(Field* field) {

/*
FieldDeclaration:
    FieldModifiersopt Type VariableDeclarators ;

VariableDeclarators:
    VariableDeclarator
    VariableDeclarators , VariableDeclarator
    //--> int a, b, c; shouldn't be possible to get from envison

VariableDeclarator:
    VariableDeclaratorId
    VariableDeclaratorId = VariableInitializer

VariableDeclaratorId:
    Identifier
    VariableDeclaratorId [ ]

VariableInitializer:
    Expression
    ArrayInitializer

FieldModifiers:
	FieldModifier
	FieldModifiers FieldModifier

FieldModifier: one of
	*Annotation
	public
	protected
	private
	*static
	*final
	*transient
	*volatile
* not in envision?
*/
	printIndent();
	printVisibility(field->visibility());
	printType(field->typeExpression()->type());
	dest_ << " " << field -> name().toStdString();
	if(field->initialValue()) {
		dest_ << " = ";
		printExpression(field->initialValue());
	}
	dest_ << ";\n";
	lines_.push_back(field);
}
void SourceBuilder::printExpression(Expression* expr) {
//TODO: typeExpressions
	if(auto arrayInitializer = dynamic_cast<ArrayInitializer*> (expr)){
		dest_ << "{";
		for(auto it = arrayInitializer->values()->begin();
				it != arrayInitializer->values()->end();it++) {
			if(it == arrayInitializer->values()->begin()) dest_ << ", ";
			//TODO: brucht das chlammere?
			dest_ << "(";
			printExpression(*it);
			dest_ << ")";
		}
		dest_ <<"}";
	}
	else if(auto binaryOperation = dynamic_cast<BinaryOperation*>(expr)){
		dest_ << "(";
		printExpression(binaryOperation->left());
		dest_ << ")";
		if(binaryOperation->op()== BinaryOperation::OperatorTypes::ARRAY_INDEX){
			dest_ << "[";
			printExpression(binaryOperation->right());
			dest_ << "]";
		}
		else{
			dest_ << "(";
			printExpression(binaryOperation->right());
			dest_ << ")";
		}
	}
	else if(auto booleanLiteral = dynamic_cast<BooleanLiteral*>(expr)) {
		if(booleanLiteral) dest_ << "true";
		else dest_ << "false";
	}
	else if(auto castExpression = dynamic_cast<CastExpression*>(expr)) {
		dest_ << "( (";
		printExpression(castExpression->castType());
		dest_ << ") (";
		printExpression(castExpression->expr());
		dest_ << ") )";
	}
	else if(auto characterLiteral = dynamic_cast<CharacterLiteral*>(expr)) {
		dest_ << "'" << characterLiteral->value().toAscii() << "'";
	}
}

void SourceBuilder::printBinaryOperator(BinaryOperation::OperatorTypes op){
	//enum OperatorTypes { TIMES, DIVIDE, REMAINDER, PLUS, MINUS,
	//LEFT_SHIFT, RIGHT_SHIFT_SIGNED, RIGHT_SHIFT_UNSIGNED,
	//LESS, GREATER, LESS_EQUALS, GREATER_EQUALS, EQUALS, NOT_EQUALS,
	//XOR, AND, OR, CONDITIONAL_AND, CONDITIONAL_OR,
	//			ARRAY_INDEX };

	switch(op){
	case BinaryOperation::TIMES: dest_ << " * "; break;
	case BinaryOperation::DIVIDE: dest_ << " / "; break;
	case BinaryOperation::REMAINDER: dest_ << " % "; break;
	case BinaryOperation::PLUS: dest_ << " + "; break;
	case BinaryOperation::MINUS: dest_ << " - "; break;
	case BinaryOperation::LEFT_SHIFT: dest_ << " << "; break;
	case BinaryOperation::RIGHT_SHIFT_SIGNED: dest_ << " >> "; break;
	case BinaryOperation::RIGHT_SHIFT_UNSIGNED: dest_ << " >>> "; break;
	case BinaryOperation::LESS: dest_ << " < "; break;
	case BinaryOperation::LESS_EQUALS: dest_ << " <= "; break;
	case BinaryOperation::GREATER_EQUALS: dest_ << " >= "; break;
	case BinaryOperation::EQUALS: dest_ << " == "; break;
	case BinaryOperation::NOT_EQUALS: dest_ << " != "; break;
	case BinaryOperation::XOR: dest_ << " ^ "; break;
	case BinaryOperation::AND: dest_ << " & "; break;
	case BinaryOperation::OR: dest_ << " | "; break;
	case BinaryOperation::CONDITIONAL_AND: dest_ << " && "; break;
	case BinaryOperation::CONDITIONAL_OR: dest_ << " || "; break;
	case BinaryOperation::ARRAY_INDEX:
		Q_ASSERT(false&&"shouldn't be printing arrayIndex here..."); break;
	default : Q_ASSERT(false&&"trying to print bad BinaryOperator enum");
	}
}

void SourceBuilder::printVisibility(Visibility::VisibilityType visibility) {
	//enum VisibilityType {DEFAULT, PUBLIC, PRIVATE, PROTECTED};
	switch (visibility)
	{
	case Visibility::VisibilityType::DEFAULT:  dest_ << ""; return;
	case Visibility::VisibilityType::PUBLIC: dest_ << "public"; break;
	case Visibility::VisibilityType::PRIVATE: dest_ << "private";break;
	case Visibility::VisibilityType::PROTECTED: dest_ << "protected";break;
	default: Q_ASSERT(false && "trying to print a bad visibility enum");
	}
	dest_ << " ";
}
}



