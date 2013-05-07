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

#include "../modelbase_api.h"

#include "../nodes/Extendable/ExtendableNode.h"
#include "../nodes/nodeMacros.h"
#include "../nodes/Text.h"

DECLARE_TYPED_LIST(MODELBASE_API, TestNodes, BinaryNode)

namespace TestNodes {

class MODELBASE_API BinaryNode: public Reflect<Model::ExtendableNode>
{
	EXTENDABLENODE_DECLARE_STANDARD_METHODS(BinaryNode)

	ATTRIBUTE(Model::Text, name, setName)
	ATTRIBUTE(BinaryNode, left, setLeft)
	ATTRIBUTE(BinaryNode, right, setRight)

	public:
		void removeLeftNode();
		void removeRightNode();

};

inline void BinaryNode::removeLeftNode() { removeOptional(leftIndex); }
inline void BinaryNode::removeRightNode() { removeOptional(rightIndex); }

}
