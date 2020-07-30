﻿#include "axistag.h"

#include <QDebug>

AxisTag::AxisTag(QCPAxis *parentAxis) : QObject(parentAxis), yAxis(parentAxis)
{
    // The dummy tracer serves here as an invisible anchor which always sticks to the right side of
    // the axis rect
    tracer = new QCPItemTracer(yAxis->parentPlot());
    tracer->setVisible(false);
    tracer->position->setTypeX(QCPItemPosition::ptAxisRectRatio);
    tracer->position->setTypeY(QCPItemPosition::ptPlotCoords);
    tracer->position->setAxisRect(yAxis->axisRect());
    tracer->position->setAxes(nullptr, yAxis);
    tracer->position->setCoords(1, 0);

    // the arrow end (head) is set to move along with the dummy tracer by setting it as its parent
    // anchor. Its coordinate system (setCoords) is thus pixels, and this is how the needed horizontal
    // offset for the tag of the second y axis is achieved. This horizontal offset gets dynamically
    // updated in AxisTag::updatePosition. the arrow "start" is simply set to have the "end" as parent
    // anchor. It is given a horizontal offset to the right, which results in a 15 pixel long arrow.
    arrow = new QCPItemLine(yAxis->parentPlot());
    arrow->setLayer("overlay");
    arrow->setClipToAxisRect(false);
    arrow->setHead(QCPLineEnding::esSpikeArrow);
    arrow->end->setParentAnchor(tracer->position);
    arrow->start->setParentAnchor(arrow->end);
    arrow->start->setCoords(35, 0);

    // The text label is anchored at the arrow start (tail) and has its "position" aligned at the
    // left, and vertically centered to the text label box.
    label = new QCPItemText(yAxis->parentPlot());
    label->setLayer("overlay");
    label->setClipToAxisRect(false);
    label->setPadding(QMargins(3, 0, 3, 0));
    label->setBrush(QBrush(Qt::white));
    label->setPositionAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    label->position->setParentAnchor(arrow->start);
}

AxisTag::~AxisTag()
{
    if (tracer)
      tracer->parentPlot()->removeItem(tracer);
    if (arrow)
      arrow->parentPlot()->removeItem(arrow);
    if (label)
      label->parentPlot()->removeItem(label);
}

void AxisTag::setText(const QString &text)
{
    label->setText(text);
}

void AxisTag::updatePosition(double value)
{
    // since both the arrow and the text label are chained to the dummy tracer (via anchor
    // parent-child relationships) it is sufficient to update the dummy tracer coordinates. The
    // Horizontal coordinate type was set to ptAxisRectRatio so to keep it aligned at the right side
    // of the axis rect, it is always kept at 1. The vertical coordinate type was set to
    // ptPlotCoordinates of the passed parent axis, so the vertical coordinate is set to the new
    // value.
    tracer->position->setCoords(1, value);

    // We want the arrow head to be at the same horizontal position as the axis backbone, even if
    // the axis has a certain offset from the axis rect border (like the added second y axis). Thus we
    // set the horizontal pixel position of the arrow end (head) to the axis offset (the pixel
    // distance to the axis rect border). This works because the parent anchor of the arrow end is
    // the dummy tracer, which, as described earlier, is tied to the right axis rect border.
    arrow->end->setCoords(yAxis->offset(), 0);
}

void AxisTag::setPen(const QPen &pen)
{
    arrow->setPen(pen);
    label->setPen(pen);
}
