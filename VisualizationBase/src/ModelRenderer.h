/***********************************************************************************************************************
**
** Copyright (c) 2011, ETH Zurich
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

/***********************************************************************************************************************
 * ModelRenderer.h
 *
 *  Created on: Dec 9, 2010
 *      Author: Dimitar Asenov
 **********************************************************************************************************************/

#ifndef MODELRENDERER_H_
#define MODELRENDERER_H_

#include "visualizationbase_api.h"
#include "ModelBase/src/nodes/Node.h"

namespace Visualization {

class Item;

class VISUALIZATIONBASE_API ModelRenderer
{
	public:
		typedef Item* (*ItemConstructor)(Item* parent, Model::Node* node);

		ModelRenderer();
		virtual ~ModelRenderer();

		virtual Item* render(Item* parent, Model::Node* node);

		void registerVisualization(int typeId, ItemConstructor visualization);

		/**
		 * Set whether default visualizations should be used.
		 *
		 * If a custom visualization is provided for a node type it will always be used. This flag only controls if a
		 * default visualization should be used in case there is no custom visualization defined.
		 *
		 * By default nodes which do not have a corresponding custom visualization will be represented with a default
		 * visualization.
		 */
		void setUseDefaultVisualizations(bool useDefault);

	private:
		QVector<ItemConstructor> visualizations;

		bool useDefaultVisualizations_;
};

inline void ModelRenderer::setUseDefaultVisualizations(bool useDefault)
{
	useDefaultVisualizations_ = useDefault;
}

template<class VIS, class NODE>
Item* createVisualization(Item* parent, Model::Node* node)
{
	return new VIS(parent, static_cast<NODE*> (node));
}



}

#endif /* MODELRENDERER_H_ */