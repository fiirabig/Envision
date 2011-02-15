/***********************************************************************************************************************
 * VNamedType.cpp
 *
 *  Created on: Feb 9, 2011
 *      Author: Dimitar Asenov
 **********************************************************************************************************************/

#include "types/VNamedType.h"

using namespace Visualization;
using namespace OOModel;

namespace OOVisualization {

ITEM_COMMON_DEFINITIONS(VNamedType)

VNamedType::VNamedType(Item* parent, NamedType* node, const VReferenceExpressionStyle* style) :
	ModelItem(parent, node, style),
	vis_( new VReferenceExpression(this, node->type(), style))
{
}

VNamedType::~VNamedType()
{
	SAFE_DELETE_ITEM(vis_);
}

void VNamedType::determineChildren()
{
	vis_->setStyle(style());
}

void VNamedType::updateGeometry(int availableWidth, int availableHeight)
{
	Item::updateGeometry(vis_, availableWidth, availableHeight);
}

bool VNamedType::focusChild(FocusTarget location)
{
	return vis_->focusChild(location);
}

}