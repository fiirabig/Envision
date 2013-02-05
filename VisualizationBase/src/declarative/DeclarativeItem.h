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

#ifndef VisualizationBase_DECLARATIVEITEM_H_
#define VisualizationBase_DECLARATIVEITEM_H_

#include "../visualizationbase_api.h"
#include "DeclarativeItemBase.h"

namespace Visualization {

class Item;

template <class VisualizationType>
class DeclarativeItem : public DeclarativeItemBase
{
	public:
		using I = VisualizationType;
		DeclarativeItem(Item* parent, const StyleType* style = itemStyles().get());
		virtual ~DeclarativeItem();
		virtual QList<Element*>& forms() override;
	protected:
		static QList<Element*>& formsStatic();
		template <class ElementType> static ElementType* addForm(ElementType* element);
};

template <class VisualizationType>
DeclarativeItem<VisualizationType>::DeclarativeItem(Item* parent, const StyleType* style) :
		DeclarativeItemBase(parent, style)
{
		static bool initialized = false;
		if(!initialized)
		{
			VisualizationType::initializeForms();
			initialized = true;
		}
}

template <class VisualizationType>
DeclarativeItem<VisualizationType>::~DeclarativeItem()
{
	for(int i=0; i<formsStatic().length(); i++)
	{
		formsStatic().at(i)->destroyChildItems(this);
	}
}

template <class VisualizationType>
QList<Element*>& DeclarativeItem<VisualizationType>::formsStatic()
{
	static QList<Element*> list;
	return list;
}

template <class VisualizationType>
QList<Element*>& DeclarativeItem<VisualizationType>::forms()
{
	return formsStatic();
}

template <class VisualizationType>
template <class ElementType>
ElementType* DeclarativeItem<VisualizationType>::addForm(ElementType* element)
{
	formsStatic().append(element);
	return element;
}

}

#endif /* VisualizationBase_DECLARATIVEITEM_H_ */