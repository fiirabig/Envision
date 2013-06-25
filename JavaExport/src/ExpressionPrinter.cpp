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


#include "ExpressionPrinter.h"
#include "OOModel/src/allOOModelNodes.h"
#include <climits>
using namespace OOModel;

namespace JavaExport {

ExpressionPrinter::ExpressionPrinter(SourcePrinter& printer):
	printer_(printer)
{
	modifierPrinter_= new ModifierPrinter(printer_);
}

ExpressionPrinter::~ExpressionPrinter()
{
	delete modifierPrinter_;
}

void ExpressionPrinter::print(OOModel::Expression* expr)
{
	printer_.startPrinting(expr);
	printExpression(expr);
	printer_.endPrinting(expr);
}

void ExpressionPrinter::printExpression(OOModel::Expression* expr)
{
	qDebug() << "printing expression " << expr;
	bool verbose = true;
	//qualifiers?

/******************************Literals******************************/
	if(auto floatLiteral = dynamic_cast<FloatLiteral*>(expr)) {
		if(verbose) qDebug() << "expression is FloatLiteral";
		QString string = QString::number(floatLiteral->value(),'f',20);
		printer_.print(string);
		printer_.print("f");

	}else if(auto booleanLiteral = dynamic_cast<BooleanLiteral*>(expr)) {
		if(verbose) qDebug() << "expression is BooleanLiteral";
		if(booleanLiteral->value()) printer_.print("true");
		else printer_.print("false");

	}else if(auto characterLiteral = dynamic_cast<CharacterLiteral*>(expr)) {
		if(verbose) qDebug() << "expression is CharacterLiteral";
		printer_.print(QString(characterLiteral->value()));

	}else if(dynamic_cast<NullLiteral*>(expr)) {
		if(verbose) qDebug() << "expression is NullLiteral ";
		printer_.print("null");

	}else if(auto integerLiteral = dynamic_cast<IntegerLiteral*>(expr)) {
		if(verbose) qDebug() << "expression is IntegerLiteral";
		printer_.print(QString::number(integerLiteral->value()));

	}else if(auto stringLiteral = dynamic_cast<StringLiteral*>(expr)) {
		if(verbose) qDebug() << "expression is StringLiteral";
		printer_.print("\"");
		printer_.print(stringLiteral->value());
		printer_.print("\"");

/***************************TypeExpressions***********************************/

	}else if(auto arrayTypeExpression = dynamic_cast<ArrayTypeExpression*>(expr)) {
		if(verbose) qDebug() << "expression is ArrayTypeExpression";
		//TODO: fixedSize??
		print(arrayTypeExpression->typeExpression());
		printer_.print("[]");

	}else if(auto classTypeExpression = dynamic_cast<ClassTypeExpression*>(expr)) {
		if(verbose) qDebug() << "expression is ClassTypeExpression";
		printer_.print(classTypeExpression->typeExpression()->name());


	}else if(auto primitiveTypeExpression = dynamic_cast<PrimitiveTypeExpression*>(expr)) {
		if(verbose) qDebug() << "expression is PrimitiveTypeExpression";
		//enum PrimitiveTypes {INT, LONG, UNSIGNED_INT, UNSIGNED_LONG,
		//FLOAT, DOUBLE, BOOLEAN, CHAR, VOID};
		switch(primitiveTypeExpression->typeValue()) {
			case PrimitiveType::INT: printer_.print("int"); break;
			case PrimitiveType::LONG: printer_.print("long"); break;
			case PrimitiveType::FLOAT: printer_.print("float"); break;
			case PrimitiveType::DOUBLE: printer_.print("double"); break;
			case PrimitiveType::BOOLEAN: printer_.print("boolean"); break;
			case PrimitiveType::CHAR: printer_.print("char"); break;
			case PrimitiveType::VOID: printer_.print("void"); break;

			case PrimitiveType::UNSIGNED_INT: Q_ASSERT(false); break;
			case PrimitiveType::UNSIGNED_LONG: Q_ASSERT(false); break;
			default: Q_ASSERT(false);
		}

/***********************UnimplementedTypeExpressions*************************/
	}else if(auto autoTypeExpression = dynamic_cast<AutoTypeExpression*>(expr)) {
		if(verbose) qDebug() << "expression is AutoTypeExpression";
		Q_ASSERT(false && autoTypeExpression);
		//TODO: try to print the type of the parents init expression
		// -> see autoExpression.type()

	}else if(auto functionTypeExpression = dynamic_cast<FunctionTypeExpression*>(expr)) {
		if(verbose) qDebug() << "expression is FunctionTypeExpression";
		//TODO:
		Q_ASSERT(false && functionTypeExpression);

	}else if(auto pointerTypeExpression = dynamic_cast<PointerTypeExpression*>(expr)) {
		if(verbose) qDebug() << "expression is PointerTypeExpression";
		//TODO:
		Q_ASSERT(false && pointerTypeExpression);

	}else if(auto referenceTypeExpression = dynamic_cast<ReferenceTypeExpression*>(expr)) {
		if(verbose) qDebug() << "expression is ReferenceTypeExpression";
		//TODO:
		Q_ASSERT(false && referenceTypeExpression);

	}else if(auto typeQualifierExpression = dynamic_cast<TypeQualifierExpression*>(expr)) {
		if(verbose) qDebug() << "expression is TypeQualifierExpression";
		//TODO:
		Q_ASSERT(false && typeQualifierExpression);

/******************************Implemented***************************/
	}else if(auto arrayInitializer = dynamic_cast<ArrayInitializer*>(expr)) {
		//TODO: if this isn't an declaration, this is not valid in java...
		if(verbose) qDebug() << "expression is ArrayInitializer";
		printer_.print(" {");
		bool first = true;
		for(auto element : *arrayInitializer->values()) {
			if(!first) printer_.print(", ");
			first = false;
			print(element);
		}
		printer_.print("}");

	}else if(auto binaryOperation = dynamic_cast<BinaryOperation*>(expr)) {
		if(verbose) qDebug() << "expression is BinaryOperation";
		//enum OperatorTypes { TIMES, DIVIDE, REMAINDER, PLUS, MINUS,
		//LEFT_SHIFT, RIGHT_SHIFT_SIGNED, RIGHT_SHIFT_UNSIGNED,
		//			LESS, GREATER, LESS_EQUALS, GREATER_EQUALS, EQUALS,
		//NOT_EQUALS, XOR, AND, OR, CONDITIONAL_AND, CONDITIONAL_OR,
		//			ARRAY_INDEX, POINTER_TO_MEMBER, POINTER_POINTER_TO_MEMBER };
		print(binaryOperation->left());
		switch(binaryOperation->op()) {
			case BinaryOperation::TIMES : printer_.print(" * "); break;
			case BinaryOperation::DIVIDE : printer_.print(" / "); break;
			case BinaryOperation::REMAINDER : printer_.print(" % "); break;
			case BinaryOperation::PLUS : printer_.print(" + "); break;
			case BinaryOperation::MINUS : printer_.print(" - "); break;
			case BinaryOperation::LEFT_SHIFT : printer_.print(" << "); break;
			case BinaryOperation::RIGHT_SHIFT_SIGNED : printer_.print(" >> "); break;
			case BinaryOperation::RIGHT_SHIFT_UNSIGNED : printer_.print(" >>> "); break;
			case BinaryOperation::LESS : printer_.print(" < "); break;
			case BinaryOperation::GREATER : printer_.print(" > "); break;
			case BinaryOperation::LESS_EQUALS : printer_.print(" <= "); break;
			case BinaryOperation::GREATER_EQUALS : printer_.print(" >= "); break;
			case BinaryOperation::EQUALS : printer_.print(" == "); break;
			case BinaryOperation::NOT_EQUALS : printer_.print(" != "); break;
			case BinaryOperation::XOR : printer_.print(" ^ "); break;
			case BinaryOperation::AND : printer_.print(" & "); break;
			case BinaryOperation::OR : printer_.print(" | "); break;
			case BinaryOperation::CONDITIONAL_AND : printer_.print(" && "); break;
			case BinaryOperation::CONDITIONAL_OR : printer_.print(" || "); break;
			case BinaryOperation::ARRAY_INDEX : printer_.print("[)"); break;
			//TODO: stimmt das?
			case BinaryOperation::POINTER_TO_MEMBER : printer_.print("."); break;
			case BinaryOperation::POINTER_POINTER_TO_MEMBER : printer_.print("."); break;
			default :Q_ASSERT(false);
		}
		print(binaryOperation->right());
		if(binaryOperation->op() == BinaryOperation::ARRAY_INDEX) {
			printer_.print("]");
		}

	}else if(auto castExpression = dynamic_cast<CastExpression*>(expr)) {
		if(verbose) qDebug() << "expression is CastExpression";
		printer_.print("(");
		print(castExpression->castType());
		qDebug() << "printed castExpression->castType()";
		printer_.print(") ");
		//TODO: (float) a+b; ?
		print(castExpression->expr());
		qDebug() << "printed castExpression->expr()";


	}else if(auto commaExpression = dynamic_cast<CommaExpression*>(expr)) {
		if(verbose) qDebug() << "expression is CommaExpression";
		print(commaExpression->left());
		printer_.print(", ");
		print(commaExpression->right());

	}else if(auto conditionalExpression = dynamic_cast<ConditionalExpression*>(expr)) {
		if(verbose) qDebug() << "expression is ConditionalExpression";
		printer_.print("if(");
		print(conditionalExpression->condition());
		printer_.print(") {");
		printer_.printNewLineAndIndent(SourcePrinter::IncrementIndent);
		print(conditionalExpression->trueExpression());
		printer_.printNewLineAndIndent(SourcePrinter::DecrementIndent);
		printer_.print("}");
		if(auto falseExpr = conditionalExpression->falseExpression()) {
			printer_.print(" else ");
			if(auto elseif = dynamic_cast<ConditionalExpression*>(falseExpr)){
				print(elseif);
			} else {
				printer_.print(" {");
				printer_.printNewLineAndIndent(SourcePrinter::IncrementIndent);
				print(falseExpr);
				printer_.printNewLineAndIndent(SourcePrinter::DecrementIndent);
				printer_.print("}");
				printer_.printNewLineAndIndent();
			}
		}else {
			printer_.printNewLineAndIndent();
		}

	}else if(dynamic_cast<ThisExpression*>(expr)) {
		if(verbose) qDebug() << "expression is ThisExpression";
		printer_.print("this");

	}else if(auto unaryOperation = dynamic_cast<UnaryOperation*>(expr)) {
		if(verbose) qDebug() << "expression is UnaryOperation";
//		enum OperatorTypes {PREINCREMENT, PREDECREMENT, POSTINCREMENT,
//			POSTDECREMENT, PLUS, MINUS, NOT, COMPLEMENT,
//						PARENTHESIS, DEREFERENCE, ADDRESSOF};
		switch(unaryOperation->op()) {
			case UnaryOperation::PREDECREMENT :
				printer_.print("--");
				print(unaryOperation->operand());
				break;
			case UnaryOperation::PREINCREMENT :
				printer_.print("++");
				print(unaryOperation->operand());
				break;
			case UnaryOperation::POSTINCREMENT :
				print(unaryOperation->operand());
				printer_.print("++");
				break;
			case UnaryOperation::POSTDECREMENT :
				print(unaryOperation->operand());
				printer_.print("--");
				break;
			case UnaryOperation::PLUS :
				printer_.print("+");
				print(unaryOperation->operand());
				//TODO: chlammere?
				break;
			case UnaryOperation::MINUS :
				printer_.print("-");
				//TODO: chlammere?
				print(unaryOperation->operand());
				break;
			case UnaryOperation::NOT :
				printer_.print("!");
				//TODO: chlammere?
				print(unaryOperation->operand());
				break;
			case UnaryOperation::PARENTHESIS :
				printer_.print("(");
				//TODO: chlammere?
				print(unaryOperation->operand());
				printer_.print(")");
				break;

			case UnaryOperation::ADDRESSOF :
			case UnaryOperation::DEREFERENCE :
			case UnaryOperation::COMPLEMENT :
			default : Q_ASSERT(false);
		}

	}else if(auto variableDeclarationExpression = dynamic_cast<VariableDeclarationExpression*>(expr)) {
		if(verbose) qDebug() << "expression is VariableDeclarationExpression";
		printVariableDeclaration(variableDeclarationExpression->decl());

	}else if(auto referenceExpression = dynamic_cast<ReferenceExpression*>(expr)) {
			if(verbose) qDebug() << "expression is ReferenceExpression";
			//TODO: prefix? okk?
			if(auto prefix = referenceExpression->prefix()) {
				print(prefix);
				printer_.print(".");
			}
			printer_.print(referenceExpression->name());
			qDebug() << "referenceExpression->name()  " << referenceExpression->name() << flush;
			//TODO: prefix??
			qDebug() << "trying to print prefix... " << referenceExpression->prefix() << flush;
			//print(referenceExpression->prefix());
	//		OOReference* ref = referenceExpression->ref();
	//		Q_ASSERT(ref->target());
	//		if ( auto project = dynamic_cast<Project*>( ref->target() ) )
	//				Q_ASSERT(false && project);
	//			else if ( auto module = dynamic_cast<Module*>( ref->target() ) )
	//				Q_ASSERT(false && module);
	//			else if ( auto cl = dynamic_cast<Class*>( ref->target() ) )
	//				Q_ASSERT(false && cl);
	//			else if ( auto alias = dynamic_cast<TypeAlias*>( ref->target() ) )
	//				Q_ASSERT(false && alias);
	//			else if ( auto nameImport = dynamic_cast<NameImport*>( ref->target() ) )
	//				Q_ASSERT(false && nameImport);
	//			else if ( auto vdecl = dynamic_cast<VariableDeclarationExpression*>( ref->target() ) )
	//				Q_ASSERT(false && vdecl);
	//			else if ( auto vdecl = dynamic_cast<VariableDeclaration*>( ref->target() ) )
	//				Q_ASSERT(false && vdecl);
	//			else if ( auto expSt = dynamic_cast<ExpressionStatement*>( ref->target() )) {
	//				if ( auto vdecl = dynamic_cast<VariableDeclarationExpression*>( expSt->expression() ) )
	//					Q_ASSERT(false && vdecl);
	//				else Q_ASSERT(false && vdecl);//ERR0R
	//			}else if ( auto field = dynamic_cast<Field*>( ref->target() ) )
	//				Q_ASSERT(false && field);
	//			else if ( auto arg = dynamic_cast<FormalArgument*>( ref->target() ) )
	//				Q_ASSERT(false && arg);
	//			else if ( auto res = dynamic_cast<FormalResult*>( ref->target() ) )
	//				Q_ASSERT(false && res);
	//			else Q_ASSERT(false);
			//TODO: typeArguments

	}else if(auto newExpression = dynamic_cast<NewExpression*>(expr)) {
		if(verbose) qDebug() << "expression is NewExpression";
		//TODO: amount??? not null if array????
		printer_.print(" new ");
		print(newExpression->newType());
		if(newExpression->amount()) {
			printer_.print("[");
			print(newExpression->amount());
			printer_.print("]");
		}

	}else if(auto methodCallExpression = dynamic_cast<MethodCallExpression*>(expr)) {
		if(verbose) qDebug() << "expression is MethodCallExpression";
			print(methodCallExpression->ref());
			printer_.print("(");
			printer_.flush();
		bool first = true;
		for(auto arg : *methodCallExpression->arguments()) {
			if(!first) printer_.print(", ");
			first = false;
			print(arg);
		}
		printer_.print(")");

/******************************Unimplemented******************************/

	}else if(auto assignmentExpression = dynamic_cast<AssignmentExpression*>(expr)) {
		if(verbose) qDebug() << "expression is AssignmentExpression";
		//TODO: Assignment is no expr in java?
//		enum AssignmentTypes { ASSIGN, PLUS_ASSIGN, MINUS_ASSIGN,
//			TIMES_ASSIGN, DIVIDE_ASSIGN, BIT_AND_ASSIGN,
//			BIT_OR_ASSIGN, BIT_XOR_ASSIGN, REMAINDER_ASSIGN,
//			LEFT_SHIFT_ASSIGN, RIGHT_SHIFT_SIGNED_ASSIGN,
//			RIGHT_SHIFT_UNSIGNED_ASSIGN};
		print(assignmentExpression->left());
		switch(assignmentExpression->op()) {
			case AssignmentExpression::ASSIGN: printer_.print(" = "); break;
			case AssignmentExpression::PLUS_ASSIGN: printer_.print(" += "); break;
			case AssignmentExpression::MINUS_ASSIGN: printer_.print(" -= "); break;
			case AssignmentExpression::TIMES_ASSIGN: printer_.print(" *= "); break;
			case AssignmentExpression::DIVIDE_ASSIGN: printer_.print(" /= "); break;
			case AssignmentExpression::BIT_AND_ASSIGN: printer_.print(" &= "); break;
			case AssignmentExpression::BIT_OR_ASSIGN: printer_.print(" |= "); break;
			case AssignmentExpression::BIT_XOR_ASSIGN: printer_.print(" ^= "); break;
			case AssignmentExpression::REMAINDER_ASSIGN: printer_.print(" %= "); break;
			case AssignmentExpression::LEFT_SHIFT_ASSIGN: printer_.print(" <<= "); break;
			case AssignmentExpression::RIGHT_SHIFT_SIGNED_ASSIGN: printer_.print(" >>= "); break;

			//TODO:
			case AssignmentExpression::RIGHT_SHIFT_UNSIGNED_ASSIGN: Q_ASSERT(false); break;
			default : Q_ASSERT(false && assignmentExpression->op());

		}
		print(assignmentExpression->right());

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

	} else Q_ASSERT(false);

}

void ExpressionPrinter::printVariableDeclaration(VariableDeclaration* decl)
{
	printer_.startPrinting(decl);
	modifierPrinter_->print(decl->modifiers());
	print(decl->typeExpression());
	printer_.print(" ");
	printer_.print(decl->name());
	if(auto initValue = decl->initialValue()) {
		printer_.print(" = ");
		print(initValue);
	}
	printer_.endPrinting(decl);
	//TODO: print ; & newline?
}
} /* namespace JavaExport */
