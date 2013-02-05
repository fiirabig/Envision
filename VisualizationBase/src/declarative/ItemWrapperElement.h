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

template <class ParentType, class ChildItemType = Item>
class ItemWrapperElement : public Element
{
	public: // Methods executable on element definition
		using ChildItem = ChildItemType* ParentType::*;
		ItemWrapperElement(ChildItem item);
		// TODO: if form changes, need to remove unused items
		// TODO: properly destroy all child items recursively

	public: // Methods executable when items need to be rendered
		virtual void computeSize(Item* item, int availableWidth, int availableHeight) override;
		virtual void setItemPositions(Item* item, int parentX, int parentY) override;

	public: // Recursive item destruction
		virtual void destroyChildItems(Item* item) override;

	protected:
		ChildItem item() const;

	private:
		ChildItem item_{};
};

template <class ParentType, class ChildItemType>
ItemWrapperElement<ParentType,ChildItemType>::ItemWrapperElement(ChildItem item)
: item_(item)
{}

template <class ParentType, class ChildItemType>
void ItemWrapperElement<ParentType,ChildItemType>::computeSize(Item* item, int, int)
{
	auto& childItem = (static_cast<ParentType*>(item))->*this->item();
	if(childItem)
	{
		int width = childItem->width() + leftMargin() + rightMargin();
		int height = childItem->height() + topMargin() + bottomMargin();
		setSize(QSize(width, height));
	}
	else setSize(QSize(0,0));
}

template <class ParentType, class ChildItemType>
void ItemWrapperElement<ParentType,ChildItemType>::setItemPositions(Item* item, int parentX, int parentY)
{
	auto& childItem = (static_cast<ParentType*>(item))->*this->item();
	if(childItem)
	{
		childItem->setPos(parentX + pos().x() + leftMargin(), parentY + pos().y() + topMargin());
	}
}

template <class ParentType, class ChildItemType>
void ItemWrapperElement<ParentType,ChildItemType>::destroyChildItems(Item* item)
{
	auto& childItem = (static_cast<ParentType*>(item))->*this->item();
	SAFE_DELETE_ITEM(childItem);
}

template <class ParentType, class ChildItemType>
typename ItemWrapperElement<ParentType,ChildItemType>::ChildItem
ItemWrapperElement<ParentType,ChildItemType>::item() const
{
	return item_;
}

}

#endif /* VisualizationBase_ITEMWRAPPERELEMENT_H_ */