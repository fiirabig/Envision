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

#ifndef VisualizationBase_ITEMWRAPPERELEMENT_H_
#define VisualizationBase_ITEMWRAPPERELEMENT_H_

#include "../visualizationbase_api.h"
#include "Element.h"
#include "../items/Item.h"

namespace Visualization {

template <class ParentType>
class ItemWrapperElement : public Element
{
	public: // Methods executable on element definition
		using ChildItem = Item* ParentType::*;
		ItemWrapperElement(ChildItem item);
		// TODO: if form changes, need to remove unused items

	protected:
		ChildItem item() const;

	private:
		ChildItem item_{};
};

template <class ParentType>
ItemWrapperElement<ParentType>::ItemWrapperElement(ChildItem item)
: item_(item)
{}

template <class ParentType>
typename ItemWrapperElement<ParentType>::ChildItem ItemWrapperElement<ParentType>::item() const
{
	return item_;
}

}

#endif /* VisualizationBase_ITEMWRAPPERELEMENT_H_ */
