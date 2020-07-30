#include "movingline.h"

MovingLine::MovingLine(QCPAxis *parent) : QObject(parent), yAxis(parent), lastEvent(nullptr)
{
    tracer = new QCPItemTracer(yAxis->parentPlot());
    tracer->setStyle(QCPItemTracer::tsNone);
    tracer->setGraph(yAxis->graphs()[0]);

//    tracer->position->setAxisRect(yAxis->axisRect());
//    tracer->position->setAxes(yAxis->axisRect()->axis(QCPAxis::atBottom), yAxis);
//    tracer->position->setType(QCPItemPosition::ptPlotCoords);
//    tracer->position->setCoords(0, 0);

    verticalLine = new QCPItemLine(yAxis->parentPlot());
    verticalLine->setPen(QPen(Qt::black, 1, Qt::DashLine));
    verticalLine->setClipToAxisRect(false);
    verticalLine->setLayer("overlay");

    verticalLine->start->setAxisRect(yAxis->axisRect());
    verticalLine->end->setAxisRect(yAxis->axisRect());
    verticalLine->start->setAxes(yAxis->axisRect()->axis(QCPAxis::atBottom), yAxis);
    verticalLine->end->setAxes(yAxis->axisRect()->axis(QCPAxis::atBottom), yAxis);

    label = new QCPItemText(yAxis->parentPlot());
    label->setClipToAxisRect(false);
    label->setLayer("overlay");
    label->setPadding(QMargins(3, 0, 3, 0));
    label->setBrush(QBrush(Qt::white));
//    label->setPen(yAxis->graphs()[0]->pen());
    label->setPositionAlignment(Qt::AlignCenter);

    label->position->setAxisRect(yAxis->axisRect());
    label->position->setAxes(yAxis->axisRect()->axis(QCPAxis::atBottom), yAxis);
}

MovingLine::~MovingLine()
{
    if (tracer)
      tracer->parentPlot()->removeItem(tracer);
    if (verticalLine)
      verticalLine->parentPlot()->removeItem(verticalLine);
    if (label)
      label->parentPlot()->removeItem(label);
}

void MovingLine::moveSlot(QMouseEvent *event)
{
//    double coordX = yAxis->parentPlot()->xAxis->pixelToCoord(event->pos().x());
//    double coordYTop = /*yAxis->parentPlot()->*/yAxis->range().upper;
//    double coordYBottom = /*yAxis->parentPlot()->*/yAxis->range().lower;
    double coordX = yAxis->axisRect()->axis(QCPAxis::atBottom)->pixelToCoord(event->pos().x());
    double coordYTop = yAxis->range().upper;
    double coordYBottom = yAxis->range().lower;

//    qDebug() << coordX << coordYTop << coordYBottom;

    tracer->setGraphKey(coordX);
    verticalLine->end->setCoords(coordX, coordYTop);
    verticalLine->start->setCoords(coordX, coordYBottom);

    label->position->setCoords(coordX, tracer->position->value());
    label->setText(QString::number(tracer->position->value(), 'f', 2));

    lastEvent = new QMouseEvent(*event);

//    axis->parentPlot()->replot();
}

void MovingLine::timerUpdateSlot()
{
    if (lastEvent)
    {
        moveSlot(lastEvent);
    }
}
