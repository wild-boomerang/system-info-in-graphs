#include "labels.h"

Labels::Labels(QCPAxis *parentAxis) : QObject(parentAxis), yAxis(parentAxis), minValue(-1), maxValue(-1)
{
    labelMin = new QCPItemText(yAxis->parentPlot());
    labelMin->setLayer("overlay");
    labelMin->setClipToAxisRect(false);
    labelMin->setPadding(QMargins(3, 0, 3, 0));
    labelMin->setBrush(QBrush(Qt::white));
//    labelMin->setPen(QPen(Qt::blue));
    labelMin->setColor(Qt::darkGreen);
    labelMin->setPositionAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    labelMin->position->setAxisRect(yAxis->axisRect());
    labelMin->position->setAxes(yAxis->axisRect()->axis(QCPAxis::atBottom), yAxis);
    labelMin->position->setType(QCPItemPosition::ptAxisRectRatio);
    labelMin->position->setCoords(0, 0);

    labelMax = new QCPItemText(yAxis->parentPlot());
    labelMax->setLayer("overlay");
    labelMax->setClipToAxisRect(false);
    labelMax->setPadding(QMargins(3, 0, 3, 0));
    labelMax->setBrush(QBrush(Qt::white));
//    labelMax->setPen(QPen(Qt::blue));
    labelMax->setColor(Qt::red);
    labelMax->setPositionAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    labelMax->position->setParentAnchor(labelMin->right);

    labelName = new QCPItemText(yAxis->parentPlot());
    labelName->setLayer("overlay");
    labelName->setClipToAxisRect(false);
    labelName->setPadding(QMargins(3, 0, 3, 0));
    labelName->setBrush(QBrush(Qt::white));
//    labelName->setPen(QPen(Qt::blue));
    labelName->setPositionAlignment(Qt::AlignRight | Qt::AlignVCenter);
    labelName->setText("Name of the plot");

    labelName->position->setAxisRect(yAxis->axisRect());
    labelName->position->setAxes(yAxis->axisRect()->axis(QCPAxis::atBottom), yAxis);
    labelName->position->setType(QCPItemPosition::ptAxisRectRatio);
    labelName->position->setCoords(1, 0);    
}

void Labels::UpdateData(double value)
{
   if (int(minValue) == -1 && int(maxValue) == -1)
       minValue = maxValue = value;

    if (value > maxValue)
        maxValue = value;

    if (value < minValue)
        minValue = value;

    labelMin->setText("Min: " + QString::number(minValue, 'f', 2));
    labelMax->setText("Max: " + QString::number(maxValue, 'f', 2));
}

void Labels::SetName(QString name)
{
    labelName->setText(name);
}
