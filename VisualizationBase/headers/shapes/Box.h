/***********************************************************************************************************************
 * Box.h
 *
 *  Created on: Dec 10, 2010
 *      Author: Dimitar Asenov
 **********************************************************************************************************************/

#ifndef BOX_H_
#define BOX_H_

#include "visualizationbase_api.h"

#include "Shape.h"
#include "shapes/BoxStyle.h"

namespace Visualization {

class VISUALIZATIONBASE_API Box: public Shape
{
	public:
		typedef BoxStyle StyleType;

	protected:
		qreal contentBoxWidth;
		qreal contentBoxHeight;

		QPainterPath getRectanglePath(qreal x, qreal y, int width, int height);

	public:
		Box(Item *parent, BoxStyle *style = BoxStyle::getDefault());

		BoxStyle* style() const;
		virtual void setStyle(ShapeStyle *style);

		virtual void update();
		virtual int contentLeft();
		virtual int contentTop();
		virtual int getOutterWidth(int innerWidth) const;
		virtual int getOutterHeight(int innerHeight) const;

		virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

}

#endif /* BOX_H_ */