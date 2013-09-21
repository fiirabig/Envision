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

#include "VisualizationBase/src/items/Item.h"
#include "handlers/HCommentDiagram.h"
#include "items/VCommentDiagram.h"

namespace Comments {

HCommentDiagram::HCommentDiagram()
{}

HCommentDiagram* HCommentDiagram::instance()
{
	static HCommentDiagram h;
	return &h;
}

void HCommentDiagram::keyPressEvent(Visualization::Item *target, QKeyEvent *event)
{
	auto diagram = dynamic_cast<VCommentDiagram*>(target);
	event->ignore();

	if(event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_E)
	{
		event->accept();
		diagram->toggleEditing();
	}

	if (!event->isAccepted()) GenericHandler::keyPressEvent(target, event);
}

void HCommentDiagram::mousePressEvent(Visualization::Item *target, QGraphicsSceneMouseEvent *event)
{
	auto diagram = dynamic_cast<VCommentDiagram*>(target);
	event->ignore();

	if(diagram->editing())
	{
		event->accept();

		if(event->button() == Qt::RightButton && (event->modifiers() & Qt::ShiftModifier))
		{
			originalSize_ = diagram->size();
			resizing_ = true;
		}
		else
			GenericHandler::mousePressEvent(target, event);
	}
}

void HCommentDiagram::mouseReleaseEvent(Visualization::Item *, QGraphicsSceneMouseEvent *)
{
	resizing_ = false;
}

void HCommentDiagram::mouseMoveEvent(Visualization::Item *target, QGraphicsSceneMouseEvent *event)
{
	if(resizing_)
	{
		auto diagram = dynamic_cast<VCommentDiagram*>(target);
		QPointF diff = event->pos() - event->buttonDownPos(Qt::RightButton);
		QSize newSize(originalSize_.width() + diff.x(), originalSize_.height() + diff.y());
		diagram->resize(newSize);
	}
}

void HCommentDiagram::mouseDoubleClickEvent(Visualization::Item *target, QGraphicsSceneMouseEvent *event)
{
	if(event->button() == Qt::RightButton)
	{
		// create some shape for testing shape interaction
		QPointF pos = event->buttonDownPos(Qt::RightButton);
		auto shape = new CommentDiagramShape(pos.x()-25, pos.y()-25, 50, 50, Ellipse);

		auto diagram = dynamic_cast<VCommentDiagram*>(target);
		diagram->node()->model()->beginModification(diagram->node(), "Creating a test shape");
		diagram->node()->shapes()->append(shape);
		diagram->node()->model()->endModification();
		diagram->setUpdateNeeded(Visualization::Item::StandardUpdate);
	}
}

} /* namespace Comments */
