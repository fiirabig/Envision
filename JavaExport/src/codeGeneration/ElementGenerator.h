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
#include "codeGeneration/CodeElementGenerator.h"
#include "javaCodeGeneration/JavaConfig.h"


namespace Model
{
	class Node;
	class List;
}

namespace OOModel
{
	class CatchClause;
	class Enumerator;
	class FormalArgument;
	class FormalResult;
	class FormalTypeArgument;
	class MemberInitializer;
	class Modifier;
	class OOReference;
	class StatementItem;
	class StatementItemList;
	class SwitchCase;
}

namespace JavaExport
{

class ElementGenerator: public CodeElementGenerator
{
public:
	ElementGenerator(Config config);
	virtual ~ElementGenerator();
	CodeElement* generate(Model::Node* node) const;
	virtual CodeElement* generate(Model::List* node) const;
	virtual CodeElement* generate(OOModel::CatchClause* node) const;
	virtual CodeElement* generate(OOModel::Enumerator* node) const;
	virtual CodeElement* generate(OOModel::FormalArgument* node) const;
	virtual CodeElement* generate(OOModel::FormalResult* node) const;
	virtual CodeElement* generate(OOModel::FormalTypeArgument* node) const;
	virtual CodeElement* generate(OOModel::MemberInitializer* node) const;
	virtual CodeElement* generate(OOModel::Modifier* node) const;
	virtual CodeElement* generate(OOModel::OOReference* node) const;
	virtual CodeElement* generate(OOModel::StatementItemList* node) const;
	virtual CodeElement* generate(OOModel::SwitchCase* node) const;

};



} /* namespace JavaExport */
