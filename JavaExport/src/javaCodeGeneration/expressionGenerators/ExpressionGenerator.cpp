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

#include "ExpressionGenerator.h"
#include "OOModel/src/allOOModelNodes.h"

using namespace OOModel;

namespace JavaExport
{

ExpressionGenerator::ExpressionGenerator()
{
	// TODO Auto-generated constructor stub
}

ExpressionGenerator::~ExpressionGenerator()
{
	// TODO Auto-generated destructor stub
}

CodeElement* ExpressionGenerator::generate(Expression* expr) const
{

	auto code = new Code(expr);
	if(auto floatLiteral = dynamic_cast<FloatLiteral*>(expr))
		*code <<QString::number(floatLiteral->value(),'f',20) << "f";

	else if(auto booleanLiteral = dynamic_cast<BooleanLiteral*>(expr))
	{
		if(booleanLiteral->value())
			*code << "true";
		else *code << "false";
	}

	else if(auto characterLiteral = dynamic_cast<CharacterLiteral*>(expr))
		*code << QString(characterLiteral->value());

	else if(dynamic_cast<NullLiteral*>(expr))
		*code << "null";

	else if(auto integerLiteral = dynamic_cast<IntegerLiteral*>(expr))
		*code << QString::number(integerLiteral->value());


	else if(auto stringLiteral = dynamic_cast<StringLiteral*>(expr))
		*code << "\"" << stringLiteral->value() << "\"";

	else if(auto arrayTypeExpression = dynamic_cast<ArrayTypeExpression*>(expr))
			//TODO: Ask Mitko how arrays are supposed to be
		*code << arrayTypeExpression->typeExpression() << "[]";

	else if(auto classTypeExpression = dynamic_cast<ClassTypeExpression*>(expr))
		*code << classTypeExpression->typeExpression()->name();

	else if(auto primitiveTypeExpression = dynamic_cast<PrimitiveTypeExpression*>(expr))
	{
		switch(primitiveTypeExpression->typeValue()) {
			case PrimitiveType::INT: *code << "int"; break;
			case PrimitiveType::LONG: *code << "long"; break;
			case PrimitiveType::FLOAT: *code << "float"; break;
			case PrimitiveType::DOUBLE: *code << "double"; break;
			case PrimitiveType::BOOLEAN: *code << "boolean"; break;
			case PrimitiveType::CHAR: *code << "char"; break;
			case PrimitiveType::VOID: *code << "void"; break;

			case PrimitiveType::UNSIGNED_INT: Q_ASSERT(false); break; //TODO: add error
			case PrimitiveType::UNSIGNED_LONG: Q_ASSERT(false); break;
			default: Q_ASSERT(false && "PrimitiveType enum isn't implemented completely");
		}
	}

	else if(auto autoTypeExpression = dynamic_cast<AutoTypeExpression*>(expr))
		Q_ASSERT(false && autoTypeExpression); //TODO: add error

	else if(auto functionTypeExpression = dynamic_cast<FunctionTypeExpression*>(expr))
		Q_ASSERT(false && functionTypeExpression); //TODO: add error

	else if(auto pointerTypeExpression = dynamic_cast<PointerTypeExpression*>(expr))
		Q_ASSERT(false && pointerTypeExpression); 	//TODO:

	else if(auto referenceTypeExpression = dynamic_cast<ReferenceTypeExpression*>(expr))
		Q_ASSERT(false && referenceTypeExpression); //TODO:

	else if(auto typeQualifierExpression = dynamic_cast<TypeQualifierExpression*>(expr))
		Q_ASSERT(false && typeQualifierExpression);	//TODO:

	else if(auto arrayInitializer = dynamic_cast<ArrayInitializer*>(expr))
	{
		*code << " {";
		bool first = true;
		for(auto element : *arrayInitializer->values()) {
			if(first) first = false; else *code << ", ";
			*code << element;
		}
		*code << "}";
	}

	else if(auto binaryOperation = dynamic_cast<BinaryOperation*>(expr))
	{
		*code << binaryOperation->left();

		switch(binaryOperation->op())
		{
			case BinaryOperation::TIMES : *code << " * "; break;
			case BinaryOperation::DIVIDE : *code << " / "; break;
			case BinaryOperation::REMAINDER : *code << " % "; break;
			case BinaryOperation::PLUS : *code << " + "; break;
			case BinaryOperation::MINUS : *code << " - "; break;
			case BinaryOperation::LEFT_SHIFT : *code << " << "; break;
			case BinaryOperation::RIGHT_SHIFT_SIGNED : *code << " >> "; break;
			case BinaryOperation::RIGHT_SHIFT_UNSIGNED : *code << " >>> "; break;
			case BinaryOperation::LESS : *code << " < "; break;
			case BinaryOperation::GREATER : *code << " > "; break;
			case BinaryOperation::LESS_EQUALS : *code << " <= "; break;
			case BinaryOperation::GREATER_EQUALS : *code << " >= "; break;
			case BinaryOperation::EQUALS : *code << " == "; break;
			case BinaryOperation::NOT_EQUALS : *code << " != "; break;
			case BinaryOperation::XOR : *code << " ^ "; break;
			case BinaryOperation::AND : *code << " & "; break;
			case BinaryOperation::OR : *code << " | "; break;
			case BinaryOperation::CONDITIONAL_AND : *code << " && "; break;
			case BinaryOperation::CONDITIONAL_OR : *code << " || "; break;
			case BinaryOperation::ARRAY_INDEX : *code << "[)"; break;
			//TODO: what does this mean?
			case BinaryOperation::POINTER_TO_MEMBER : *code << "."; break;
			case BinaryOperation::POINTER_POINTER_TO_MEMBER : *code << "."; break;
			default :Q_ASSERT(false && "switch on BinaryOperation");
		}
		*code << binaryOperation->right();
		if(binaryOperation->op() == BinaryOperation::ARRAY_INDEX)
			*code << "]";
	}

	else if(auto castExpression = dynamic_cast<CastExpression*>(expr))
		*code << "(" << castExpression->castType() << ") " << castExpression->expr();

	else if(auto commaExpression = dynamic_cast<CommaExpression*>(expr))
		*code << commaExpression->left() << ", " << commaExpression->right();

	else if(auto cond = dynamic_cast<ConditionalExpression*>(expr))
		*code << cond->condition() << " ? "<< cond->trueExpression() << " : " << cond->trueExpression();

	else if(dynamic_cast<ThisExpression*>(expr))
		*code << "this";

	else if(auto unaryOperation = dynamic_cast<UnaryOperation*>(expr))
	{
		switch(unaryOperation->op())
		{
			case UnaryOperation::PREDECREMENT :
				*code << "--" << unaryOperation->operand(); break;
			case UnaryOperation::PREINCREMENT :
				*code << "++" << unaryOperation->operand(); break;
			case UnaryOperation::POSTINCREMENT :
				*code << unaryOperation->operand() << "--" ; break;
			case UnaryOperation::POSTDECREMENT :
				*code << unaryOperation->operand() << "++" ; break;
			case UnaryOperation::PLUS :
				*code << "+" << unaryOperation->operand(); break;
				//TODO: parenthesis?
				break;
			case UnaryOperation::MINUS :
				*code << "-" << unaryOperation->operand(); break;
				//TODO: parenthesis?
			case UnaryOperation::NOT :
				*code << "!" << unaryOperation->operand(); break;
				//TODO: parenthesis?
			case UnaryOperation::PARENTHESIS :
				*code << "(" << unaryOperation->operand() << ")"; break;
				//TODO: parenthesis?
			case UnaryOperation::ADDRESSOF : //TODO: add error
			case UnaryOperation::DEREFERENCE :
			case UnaryOperation::COMPLEMENT :
			default : Q_ASSERT(false && "switch on UnaryOperator");
		}
	}

	else if(auto variableDeclarationExpression = dynamic_cast<VariableDeclarationExpression*>(expr))
		*code << variableDeclarationExpression->decl();

	else if(auto referenceExpression = dynamic_cast<ReferenceExpression*>(expr))
	{
		//TODO: ask mitko if this is ok
		if(auto prefix = referenceExpression->prefix())
			*code << prefix << ".";

		*code << referenceExpression->name();

		auto typeArgs = referenceExpression->typeArguments();
		if(typeArgs->size() > 0)
		{
			*code << "<";
			bool first = true;
			for(auto arg : *typeArgs)
			{
				if(first) first = false; else *code << ", ";
				*code << arg;
			}
			*code << ">";
		}
	}

	else if(auto newExpression = dynamic_cast<NewExpression*>(expr))
	//TODO: amount??? not null if array???? ask mitko
	{
		*code << "new " << newExpression->newType();
		if(newExpression->amount())
			*code << "[" << newExpression->amount() << "]";
	}

	else if(auto methodCallExpression = dynamic_cast<MethodCallExpression*>(expr))
	{
		*code << methodCallExpression->callee() << "(";
		bool first = true;
		for(auto arg : *methodCallExpression->arguments())
		{
				if(first) first = false; else *code << ", ";
				*code << arg;
		}
		*code << ")";
	}

	else if(auto assignmentExpression = dynamic_cast<AssignmentExpression*>(expr))
	{
		*code << assignmentExpression->left();
		switch(assignmentExpression->op())
		{
			case AssignmentExpression::ASSIGN: *code << " = "; break;
			case AssignmentExpression::PLUS_ASSIGN: *code << " += "; break;
			case AssignmentExpression::MINUS_ASSIGN: *code << " -= "; break;
			case AssignmentExpression::TIMES_ASSIGN: *code << " *= "; break;
			case AssignmentExpression::DIVIDE_ASSIGN: *code << " /= "; break;
			case AssignmentExpression::BIT_AND_ASSIGN: *code << " &= "; break;
			case AssignmentExpression::BIT_OR_ASSIGN: *code << " |= "; break;
			case AssignmentExpression::BIT_XOR_ASSIGN: *code << " ^= "; break;
			case AssignmentExpression::REMAINDER_ASSIGN: *code << " %= "; break;
			case AssignmentExpression::LEFT_SHIFT_ASSIGN: *code << " <<= "; break;
			case AssignmentExpression::RIGHT_SHIFT_SIGNED_ASSIGN: *code << " >>= "; break;

			//TODO:
			case AssignmentExpression::RIGHT_SHIFT_UNSIGNED_ASSIGN: Q_ASSERT(false); break; //TODO: add error
			default : Q_ASSERT(false && assignmentExpression->op());

		}
		*code << assignmentExpression->right();
	}



	/*
	 *
	}else if(auto deleteExpression = dynamic_cast<DeleteExpression*>(expr)) {
		if(verbose) qDebug() << "expression is DeleteExpression";
		//TODO:
		Q_ASSERT(false && deleteExpression);

	}else if(auto emptyExpression = dynamic_cast<EmptyExpression*>(expr)) {
		if(verbose) qDebug() << "expression is EmptyExpression";
		//TODO:
		Q_ASSERT(false && emptyExpression);

	}else if(auto errorExpression = dynamic_cast<ErrorExpression*>(expr)) {
		if(verbose) qDebug() << "expression is ErrorExpression";
		//TODO:
		Q_ASSERT(false && errorExpression);

	}else if(auto lambdaExpression = dynamic_cast<LambdaExpression*>(expr)) {
		if(verbose) qDebug() << "expression is LambdaExpression";
		//TODO:
		Q_ASSERT(false && lambdaExpression);

	}else if(auto throwExpression = dynamic_cast<ThrowExpression*>(expr)) {
		if(verbose) qDebug() << "expression is ThrowExpression";
		//TODO:
		Q_ASSERT(false && throwExpression);

	}else if(auto typeTraitExpression = dynamic_cast<TypeTraitExpression*>(expr)) {
		if(verbose) qDebug() << "expression is TypeTraitExpression";
		//TODO:
		Q_ASSERT(false && typeTraitExpression);

	}else if(auto unfinishedOperator = dynamic_cast<UnfinishedOperator*>(expr)) {
		if(verbose) qDebug() << "expression is UnfinishedOperator";
		//TODO:
		Q_ASSERT(false && unfinishedOperator);
	 *
	 */


	else
	{
		qDebug() << "unimplemented " << expr->symbolName();
		Q_ASSERT(false && "unimplemented");
	}

	return code;

	qDebug() << "unimplemented " << expr->symbolName();
	Q_ASSERT(false && "unimplemented");
	return nullptr;
}

} /* namespace JavaExport */
