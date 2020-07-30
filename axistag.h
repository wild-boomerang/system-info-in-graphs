#ifndef AXISTAG_H
#define AXISTAG_H

#include <QObject>

#include "qcustomplot.h"

class AxisTag : public QObject
{
    Q_OBJECT
public:
    explicit AxisTag(QCPAxis *parentAxis);
    ~AxisTag();

    void setText(const QString &text);
    void updatePosition(double value);
    void setPen(const QPen &pen);

private:
    QCPAxis *yAxis;
    QPointer<QCPItemTracer> tracer;
    QPointer<QCPItemLine> arrow;
    QPointer<QCPItemText> label;
};

#endif // AXISTAG_H
