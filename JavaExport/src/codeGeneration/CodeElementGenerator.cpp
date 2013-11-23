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

#include "CodeElementGenerator.h"
#include "ModelBase/src/nodes/Node.h"
#include "ModelBase/src/nodes/List.h"


namespace JavaExport
{

CodeElementGenerator::CodeElementGenerator(Config config) : config_(config)
{
	// TODO Auto-generated constructor stub

}

CodeElementGenerator::~CodeElementGenerator() {
	// TODO Auto-generated destructor stub
}

Scope* CodeElementGenerator::curlyBraces(Model::Node* node, Model::Node* content) const
{
	auto scope = curlyBraces(node);
	*scope << content;
	return scope;
}

Scope* CodeElementGenerator::curlyBraces(Model::Node* node) const
{
	auto scope = new Scope(node,config_.curlyBraces());
	return scope;
}

Scope* CodeElementGenerator::parenthesis(Model::Node* node) const
{
	auto scope = new Scope(node,config_.parentheses());
	return scope;
}
Scope* CodeElementGenerator::parenthesis(Model::Node* node, Model::Node* content) const
{
	auto scope = parenthesis(node);
	*scope << content;
	return scope;
}

CodeElement* CodeElementGenerator::allowedWithExactAmount(Model::List* list,
		int amount, QString parentName, QString childName, QString first,
		QString separator, QString last) const
{
	if(list->size() == amount)
		return new Sequence(list,first,separator,last);
	return new NotAllowed(list,"in " + config_.languageName() + " a " + parentName + " must have exactly "
			+ QString::number(amount) + " " + childName + ". This " + parentName + " has "
			+ QString::number(list->size()));
}

CodeElement* CodeElementGenerator::allowedWithExactAmount(Model::List* list,
		int amount, QString parentName, QString childName, QString first,
		QString last) const
{
	return allowedWithExactAmount(list, amount, parentName, childName, first, "", last);
}

CodeElement* CodeElementGenerator::allowedWithExactAmount(Model::List* list,
		int amount, QString parentName, QString childName,
		QString separator) const
{
	return allowedWithExactAmount(list, amount, parentName, childName, "", separator, "");
}

CodeElement* CodeElementGenerator::allowedWithExactAmount(Model::List* list,
		int amount, QString parentName, QString childName) const
{
	return allowedWithExactAmount(list, amount, parentName, childName, "", "", "");

}

CodeElement* CodeElementGenerator::allowedWithMinimumAmount(Model::List* list,
		int amount, QString parentName, QString childName, QString first,
		QString separator, QString last) const
{
	if(list->size() <= amount)
		return new Sequence(list,first,separator,last);
	return new NotAllowed(list,"in " + config_.languageName() + " a " + parentName + " must have at least "
			+ QString::number(amount) + " " + childName + ". This " + parentName + " has "
			+ QString::number(list->size()));
}

CodeElement* CodeElementGenerator::allowedWithMinimumAmount(Model::List* list,
		int amount, QString parentName, QString childName, QString first,
		QString last) const
{
	return allowedWithMinimumAmount(list, amount, parentName, childName, first, "", last);
}

CodeElement* CodeElementGenerator::allowedWithMinimumAmount(Model::List* list,
		int amount, QString parentName, QString childName,
		QString separator) const
{
	return allowedWithMinimumAmount(list, amount, parentName, childName, "", separator, "");

}

CodeElement* CodeElementGenerator::allowedWithMinimumAmount(Model::List* list,
		int amount, QString parentName, QString childName) const
{
	return allowedWithMinimumAmount(list, amount, parentName, childName, "", "", "");
}

CodeElement* CodeElementGenerator::allowedWithMaximumAmount(Model::List* list,
		int amount, QString parentName, QString childName, QString first,
		QString separator, QString last) const
{
	if(list->size() >= amount)
		return new Sequence(list,first,separator,last);
	return new NotAllowed(list,"in " + config_.languageName() + " a " + parentName + " must have at most  "
			+ QString::number(amount) + " " + childName + ". This " + parentName + " has "
			+ QString::number(list->size()));
}

CodeElement* CodeElementGenerator::allowedWithMaximumAmount(Model::List* list,
		int amount, QString parentName, QString childName, QString first,
		QString last) const
{
	return allowedWithMaximumAmount(list, amount, parentName, childName, first, "", last);
}

CodeElement* CodeElementGenerator::allowedWithMaximumAmount(Model::List* list,
		int amount, QString parentName, QString childName,
		QString separator) const
{
	return allowedWithMaximumAmount(list, amount, parentName, childName, "", separator, "");
}

CodeElement* CodeElementGenerator::allowedWithMaximumAmount(Model::List* list,
		int amount, QString parentName, QString childName) const
{
	return allowedWithMaximumAmount(list, amount, parentName, childName, "", "", "");
}

} /* namespace JavaExport */
