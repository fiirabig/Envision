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

#include "StatementItemGenerator.h"
#include "OOModel/src/elements/StatementItem.h"
#include "OOModel/src/statements/Block.h"
#include "OOModel/src/statements/BreakStatement.h"
#include "OOModel/src/statements/ContinueStatement.h"
#include "OOModel/src/statements/DeclarationStatement.h"
#include "OOModel/src/statements/ExpressionStatement.h"
#include "OOModel/src/statements/ForEachStatement.h"
#include "OOModel/src/statements/IfStatement.h"
#include "OOModel/src/statements/LoopStatement.h"
#include "OOModel/src/statements/ReturnStatement.h"
#include "OOModel/src/statements/Statement.h"
#include "OOModel/src/statements/SwitchStatement.h"
#include "OOModel/src/statements/TryCatchFinallyStatement.h"
#include "OOModel/src/statements/CaseStatement.h"


namespace JavaExport
{

StatementItemGenerator::StatementItemGenerator(Config config)
: CodeElementGenerator(config) {}

CodeElement* StatementItemGenerator::generate(OOModel::StatementItem* statement) const
{
	if(auto stmt = dynamic_cast<OOModel::Block*>(statement))
		return generate(stmt);
	else if(auto stmt = dynamic_cast<OOModel::BreakStatement*>(statement))
		return generate(stmt);
	else if(auto stmt = dynamic_cast<OOModel::ContinueStatement*>(statement))
		return generate(stmt);
	else if(auto stmt = dynamic_cast<OOModel::DeclarationStatement*>(statement))
		return generate(stmt);
	else if(auto stmt = dynamic_cast<OOModel::ExpressionStatement*>(statement))
		return generate(stmt);
	else if(auto stmt = dynamic_cast<OOModel::ForEachStatement*>(statement))
		return generate(stmt);
	else if(auto stmt = dynamic_cast<OOModel::IfStatement*>(statement))
		return generate(stmt);
	else if(auto stmt = dynamic_cast<OOModel::LoopStatement*>(statement))
		return generate(stmt);
	else if(auto stmt = dynamic_cast<OOModel::ReturnStatement*>(statement))
		return generate(stmt);
	else if(auto stmt = dynamic_cast<OOModel::SwitchStatement*>(statement))
		return generate(stmt);
	else if(auto stmt = dynamic_cast<OOModel::TryCatchFinallyStatement*>(statement))
		return generate(stmt);
	else if(auto stmt = dynamic_cast<OOModel::CaseStatement*>(statement))
		return generate(stmt);
	else if(auto stmt = dynamic_cast<OOModel::Statement*>(statement))
		return generate(stmt);
	else
		return unimplemented(statement);
}

CodeElement* StatementItemGenerator::generate(OOModel::Block* statement) const
{
	return unimplemented(statement);
}


CodeElement* StatementItemGenerator::generate(OOModel::BreakStatement* statement) const
{
	return unimplemented(statement);
}

CodeElement* StatementItemGenerator::generate(OOModel::ContinueStatement* statement) const
{
	return unimplemented(statement);
}


CodeElement* StatementItemGenerator::generate(OOModel::DeclarationStatement* statement) const
{
	return unimplemented(statement);
}

CodeElement* StatementItemGenerator::generate(OOModel::ExpressionStatement* statement) const
{
	return unimplemented(statement);
}


CodeElement* StatementItemGenerator::generate(OOModel::ForEachStatement* statement) const
{
	return unimplemented(statement);
}

CodeElement* StatementItemGenerator::generate(OOModel::IfStatement* statement) const
{
	return unimplemented(statement);
}

CodeElement* StatementItemGenerator::generate(OOModel::LoopStatement* statement) const
{
	return unimplemented(statement);
}

CodeElement* StatementItemGenerator::generate(OOModel::ReturnStatement* statement) const
{
	return unimplemented(statement);
}

CodeElement* StatementItemGenerator::generate(OOModel::Statement* statement) const
{
	return unimplemented(statement);
}

CodeElement* StatementItemGenerator::generate(OOModel::SwitchStatement* statement) const
{
	return unimplemented(statement);
}

CodeElement* StatementItemGenerator::generate(OOModel::TryCatchFinallyStatement* statement) const
{
	return unimplemented(statement);
}

CodeElement* StatementItemGenerator::generate(OOModel::CaseStatement* statement) const
{
	return unimplemented(statement);
}

} /* namespace JavaExport */
