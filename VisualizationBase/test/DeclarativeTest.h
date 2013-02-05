/***********************************************************************************************************************
 **
 ** Copyright (c) 2011, 2013 ETH Zurich
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

#ifndef VisualizationBase_DECLARATIVETEST_H_
#define VisualizationBase_DECLARATIVETEST_H_

#include "../src/declarative/DeclarativeItem.h"
#include "../src/declarative/ItemWrapperElement.h"
#include "../src/items/SymbolStyle.h"

namespace TestNodes {
class BinaryNode;
}

namespace Visualization {

class Item;
class Symbol;
class VExtendable;

class DeclarativeTest : public DeclarativeItem<DeclarativeTest> {

	ITEM_COMMON_CUSTOM_STYLENAME(DeclarativeTest, SymbolStyle)

	public:
		DeclarativeTest(Item* parent, TestNodes::BinaryNode* node);
		static void initializeForms();

	private:
		typedef DeclarativeItem<DeclarativeTest> BaseItemType;
		Symbol* testItem_{};
		Symbol* testItem2_{};
		Symbol* testItem3_{};
		Symbol* testItem4_{};
		VExtendable* testNodeItem_{};
		Item* testNodeItemGeneral_{};
		TestNodes::BinaryNode* testNode_{};
};

} /* namespace Visualization */

#endif /* VisualizationBase_DECLARATIVETEST_H_ */