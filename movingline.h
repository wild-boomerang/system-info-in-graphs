#ifndef MOVINGLINE_H
#define MOVINGLINE_H

#include <QObject>

#include "qcustomplot.h"

class MovingLine : public QObject
{
    Q_OBJECT
public:
    explicit MovingLine(QCPAxis *parent);
    ~MovingLine();

    void moveSlot(QMouseEvent *event);
    void timerUpdateSlot();

private:
    QCPAxis *yAxis;
    QMouseEvent *lastEvent;

    QPointer<QCPItemLine> verticalLine;
    QPointer<QCPItemText> label;
    QPointer<QCPItemTracer> tracer;
};

#endif // MOVINGLINE_H
