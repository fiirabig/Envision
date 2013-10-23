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

#include "handlers/HCommentDiagramConnector.h"
#include "items/VCommentDiagram.h"
#include "items/VCommentDiagramConnector.h"

namespace Comments {

HCommentDiagramConnector::HCommentDiagramConnector()
{}

HCommentDiagramConnector* HCommentDiagramConnector::instance()
{
	static HCommentDiagramConnector h;
	return &h;
}

void HCommentDiagramConnector::keyPressEvent(Visualization::Item *target, QKeyEvent *event)
{
	auto connector = dynamic_cast<VCommentDiagramConnector*>(target);
	event->ignore();

	if(connector->diagram()->editing())
	{
		if(event->modifiers() == Qt::NoModifier && event->key() == Qt::Key_Delete)
		{
			event->accept();
			connector->diagram()->node()->removeConnector(connector->node());
			// since the connector was selected, we need to clear the selection
			auto scene = target->scene();
			scene->clearFocus();
			scene->clearSelection();
			scene->setMainCursor(nullptr);
		}
	}

	if (!event->isAccepted())
		GenericHandler::keyPressEvent(target, event);
}

void HCommentDiagramConnector::mousePressEvent(Visualization::Item*, QGraphicsSceneMouseEvent *event)
{
	event->ignore();
}

void HCommentDiagramConnector::mouseReleaseEvent(Visualization::Item*, QGraphicsSceneMouseEvent *event)
{
	event->ignore();
}

void HCommentDiagramConnector::mouseMoveEvent(Visualization::Item*, QGraphicsSceneMouseEvent *event)
{
	event->ignore();
}

void HCommentDiagramConnector::mouseDoubleClickEvent(Visualization::Item*, QGraphicsSceneMouseEvent *event)
{
	event->ignore();
}

} /* namespace Comments */