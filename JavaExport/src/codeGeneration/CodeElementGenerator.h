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

#pragma once
#include "codeGeneration/Config.h"
#include "codeGeneration/CodeElement.h"

namespace Model
{
	class Node;
	class List;
}
namespace JavaExport
{

class CodeElementGenerator
{
public:
	CodeElementGenerator(Config layoutConfig);
	virtual ~CodeElementGenerator();

	Scope* curlyBraces(Model::Node* node) const;
	Scope* curlyBraces(Model::Node* node, Model::Node* content) const;
	Scope* parenthesis(Model::Node* node) const;
	Scope* parenthesis(Model::Node* node, Model::Node* content) const;
	Unimplemented* unimplemented(Model::Node* node) const;
	CodeElement* notAllowed(Model::Node* node) const;
	CodeElement* allowedWithExactAmount(Model::List* list, int amount,QString parentName, QString childName,
			QString first, QString separator, QString last) const;
	CodeElement* allowedWithExactAmount(Model::List* list, int amount,QString parentName, QString childName,
			QString first, QString last) const;
	CodeElement* allowedWithExactAmount(Model::List* list, int amount,QString parentName, QString childName,
			QString separator) const;
	CodeElement* allowedWithExactAmount(Model::List* list, int amount, QString parentName, QString childName) const;
	CodeElement* allowedWithMinimumAmount(Model::List* list, int amount, QString parentName, QString childName,
			QString first, QString separator, QString last) const;
	CodeElement* allowedWithMinimumAmount(Model::List* list, int amount,QString parentName, QString childName,
			QString first, QString last) const;
	CodeElement* allowedWithMinimumAmount(Model::List* list, int amount,QString parentName, QString childName,
			QString separator) const;
	CodeElement* allowedWithMinimumAmount(Model::List* list, int amount, QString parentName, QString childName) const;
	CodeElement* allowedWithMaximumAmount(Model::List* list, int amount,QString parentName, QString childName,
			QString first, QString separator, QString last) const;
	CodeElement* allowedWithMaximumAmount(Model::List* list, int amount, QString parentName, QString childName,
			QString first, QString last) const;
	CodeElement* allowedWithMaximumAmount(Model::List* list, int amount, QString parentName, QString childName,
			QString separator) const;
	CodeElement* allowedWithMaximumAmount(Model::List* list, int amount,QString parentName, QString childName) const;


private:
	Config config_;
};


inline Unimplemented* CodeElementGenerator::unimplemented(Model::Node* node) const
{
	return new Unimplemented(node, config_.languageName());
}

inline CodeElement* CodeElementGenerator::notAllowed(Model::Node* node) const
{
	if(auto list = dynamic_cast<Model::List*>(node))
		if(list->size() == 0)
			return new Ignore(list);
	return new NotAllowed(node, config_.notAllowedString());
}

} /* namespace JavaExport */
