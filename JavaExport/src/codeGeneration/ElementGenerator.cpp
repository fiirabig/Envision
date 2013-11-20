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

#include "ElementGenerator.h"

#include "ModelBase/src/nodes/Node.h"
#include "ModelBase/src/nodes/List.h"

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

ElementGenerator::ElementGenerator(Config config) : CodeElementGenerator(config)
{
	// TODO Auto-generated constructor stub
}

ElementGenerator::~ElementGenerator()
{
	// TODO Auto-generated destructor stub
}


CodeElement* ElementGenerator::generate(Model::Node* node) const
{
	//Carefull: statementItemList must come before list, because it wouldn't get
	//called otherwise
	if(auto statementItemList = dynamic_cast<OOModel::StatementItemList*>(node))
		return generate(statementItemList);
	else if(auto list = dynamic_cast<Model::List*>(node))
		return generate(list);
	else if(auto catchClause = dynamic_cast<OOModel::CatchClause*>(node))
		return generate(catchClause);
	else if(auto enumerator = dynamic_cast<OOModel::Enumerator*>(node))
		return generate(enumerator);
	else if(auto formalArgument = dynamic_cast<OOModel::FormalArgument*>(node))
		return generate(formalArgument);
	else if(auto formalResult = dynamic_cast<OOModel::FormalResult*>(node))
		return generate(formalResult);
	else if(auto formalTypeArgument = dynamic_cast<OOModel::FormalTypeArgument*>(node))
		return generate(formalTypeArgument);
	else if(auto memberInitializer = dynamic_cast<OOModel::MemberInitializer*>(node))
		return generate(memberInitializer);
	else if(auto modifier = dynamic_cast<OOModel::Modifier*>(node))
		return generate(modifier);
	else if(auto oOReference = dynamic_cast<OOModel::OOReference*>(node))
		return generate(oOReference);
	else if(auto scase = dynamic_cast<OOModel::SwitchCase*>(node))
		return generate(scase);

	return unimplemented(node);

}

CodeElement* ElementGenerator::generate(Model::List* node) const
{
	return new Sequence(node);
}


CodeElement* ElementGenerator::generate(OOModel::CatchClause* node) const
{
	return unimplemented(node);
}

CodeElement* ElementGenerator::generate(OOModel::Enumerator* node) const
{
	return unimplemented(node);
}


CodeElement* ElementGenerator::generate(OOModel::FormalArgument* node) const
{
	return unimplemented(node);
}


CodeElement* ElementGenerator::generate(OOModel::FormalResult* node) const
{
	return unimplemented(node);
}

CodeElement* ElementGenerator::generate(OOModel::FormalTypeArgument* node) const
{
	return unimplemented(node);
}

CodeElement* ElementGenerator::generate(OOModel::MemberInitializer* node) const
{
	return unimplemented(node);
}

CodeElement* ElementGenerator::generate(OOModel::Modifier* node) const
{
	return unimplemented(node);
}

CodeElement* ElementGenerator::generate(OOModel::OOReference* node) const
{
	return unimplemented(node);
}


CodeElement* ElementGenerator::generate(OOModel::StatementItemList* node) const
{
	return unimplemented(node);
}

CodeElement* ElementGenerator::generate(OOModel::SwitchCase* node) const
{
	return unimplemented(node);
}

} /* namespace JavaExport */
