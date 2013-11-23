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

namespace OOModel
{
	class StatementItem;
	class Block;
	class BreakStatement;
	class ContinueStatement;
	class DeclarationStatement;
	class ExpressionStatement;
	class ForEachStatement;
	class IfStatement;
	class LoopStatement;
	class ReturnStatement;
	class Statement;
	class SwitchStatement;
	class TryCatchFinallyStatement;
	class CaseStatement;
}
namespace JavaExport
{

class StatementItemGenerator: public CodeElementGenerator
{
public:
	StatementItemGenerator(Config config);
	virtual ~StatementItemGenerator();
	CodeElement* generate(OOModel::StatementItem* statement) const;
	virtual CodeElement* generate(OOModel::Block* statement) const;
	virtual CodeElement* generate(OOModel::BreakStatement* statement) const;
	virtual CodeElement* generate(OOModel::ContinueStatement* statement) const;
	virtual CodeElement* generate(OOModel::DeclarationStatement* statement) const;
	virtual CodeElement* generate(OOModel::ExpressionStatement* statement) const;
	virtual CodeElement* generate(OOModel::ForEachStatement* statement) const;
	virtual CodeElement* generate(OOModel::IfStatement* statement) const;
	virtual CodeElement* generate(OOModel::LoopStatement* statement) const;
	virtual CodeElement* generate(OOModel::ReturnStatement* statement) const;
	virtual CodeElement* generate(OOModel::Statement* statement) const;
	virtual CodeElement* generate(OOModel::SwitchStatement* statement) const;
	virtual CodeElement* generate(OOModel::TryCatchFinallyStatement* statement) const;
	virtual CodeElement* generate(OOModel::CaseStatement* statement) const;


};

} /* namespace JavaExport */
