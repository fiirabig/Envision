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

#include "JavaElementGenerator.h"
#include "JavaConfig.h"

#include "OOModel/src/elements/CatchClause.h"
#include "OOModel/src/elements/Enumerator.h"
#include "OOModel/src/elements/FormalArgument.h"
#include "OOModel/src/elements/FormalResult.h"
#include "OOModel/src/elements/FormalTypeArgument.h"
#include "OOModel/src/elements/MemberInitializer.h"
#include "OOModel/src/elements/Modifier.h"
#include "OOModel/src/elements/OOReference.h"
#include "OOModel/src/elements/StatementItemList.h"
#include "OOModel/src/statements/SwitchCase.h"


namespace JavaExport
{

JavaElementGenerator::JavaElementGenerator() : ElementGenerator(javaConfig())
{
	// TODO Auto-generated constructor stub
}

JavaElementGenerator::~JavaElementGenerator()
{
	// TODO Auto-generated destructor stub
}

CodeElement* JavaElementGenerator::generate(OOModel::CatchClause* catchClause) const
{
	//ATTRIBUTE(Expression, exceptionToCatch, setExceptionToCatch)
	//ATTRIBUTE(StatementItemList, body, setBody)

	//TODO: exception has two bodies? ask mitko
	//try {...} catch(Exception e) {...}
	auto code = new Code(catchClause);
	*code << "catch" << parenthesis(catchClause,catchClause->exceptionToCatch())
			<< curlyBraces(catchClause,catchClause->body());
	return code;
}


CodeElement* JavaElementGenerator::generate(OOModel::Enumerator* enumerator) const
{
//	ATTRIBUTE_OOP_NAME
//	ATTRIBUTE(Expression, value, setValue)

	//TODO: ask Mitko && test
	auto code = new Code(enumerator);
	*code << "enum" << enumerator->value();
	return code;
}

CodeElement* JavaElementGenerator::generate(OOModel::FormalArgument* arg) const
{
	//TODO: ask Mitko
//	PRIVATE_ATTRIBUTE_VALUE(Model::Integer, directionInt, setDirectionInt, int)

	auto code = new Code(arg);
	*code << arg->typeExpression() << " " << arg->name();
	return code;
}

CodeElement* JavaElementGenerator::generate(OOModel::FormalResult* result) const
{
	auto code = new Code(result);
	*code << result->typeExpression(); //TODO: << new Ignore(result->name());
	return code;
}

CodeElement* JavaElementGenerator::generate(OOModel::FormalTypeArgument* arg) const
{
	//TODO: Java can have more than one subtype
	auto code = new Code(arg);
	*code << arg->name();
	if(arg->subTypeOfExpression()) *code << " extends " << arg->subTypeOfExpression();
	if(arg->superTypeOfExpression()) *code << " super " << arg->superTypeOfExpression();
	return code;
}

CodeElement* JavaElementGenerator::generate(OOModel::MemberInitializer* node) const
{
	//TODO: ask Mitko
	return notAllowed(node);
}

CodeElement* JavaElementGenerator::generate(OOModel::Modifier* modifier) const
{
	auto code = new Code(modifier);

	bool first = true;
	if(modifier->isSet(OOModel::Modifier::Public))
	{
		if(first) first = false; else *code << " ";
		*code << ("public");
	}
	if(modifier->isSet(OOModel::Modifier::Private))
	{
		if(first) first = false; else *code << " ";
		*code << ("private");
	}
	if(modifier->isSet(OOModel::Modifier::Protected))
	{
		if(first) first = false; else *code << " ";
		*code << ("protected");
	}
	if(modifier->isSet(OOModel::Modifier::Static))
	{
		if(first) first = false; else *code << " ";
		*code << ("static");
	}
	if(modifier->isSet(OOModel::Modifier::Final))
	{
		//TODO: ask mitko
		Q_ASSERT(false && "peep");
		if(first) first = false; else *code << " ";
		*code << ("final");
	}
	if(modifier->isSet(OOModel::Modifier::Abstract))
	{
		if(first) first = false; else *code << " ";
		*code << ("abstract");
	}
	if(modifier->isSet(OOModel::Modifier::Virtual))
	{
		*code << new NotAllowed(modifier, "there is no virtual keyword in Java");
	}
	if(modifier->isSet(OOModel::Modifier::Override))
	{
		*code << new NotAllowed(modifier, "there is no override keyword in Java");
	}
	if(modifier->isSet(OOModel::Modifier::Inline))
	{
		*code << new NotAllowed(modifier, "there is no inline keyword in Java");
	}
	if(!first) *code << " ";

	return code;
}

CodeElement* JavaElementGenerator::generate(OOModel::OOReference* ref) const
{
	//TODO: ask Mitko
	return new CodeElement(ref->target());
}

CodeElement* JavaElementGenerator::generate(OOModel::StatementItemList* items) const
{
	auto code = curlyBraces(items);
	*code << new Sequence(items);
	return code;
}

CodeElement* JavaElementGenerator::generate(OOModel::SwitchCase* scase) const
{
	//TODO: test
	auto code = new Code(scase);
	*code << "case " << scase->expr();
	auto scope = new Scope(scase,ScopeLayout(":","",true,false,true,false,false));
	*code << scope;
	*scope << scase->statement();
	return code;
}

} /* namespace JavaExport */
