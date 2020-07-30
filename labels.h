#ifndef LABELS_H
#define LABELS_H

#include <QObject>

#include "qcustomplot.h"

class Labels : public QObject
{
    Q_OBJECT
public:
    explicit Labels(QCPAxis *parentAxis);

    void UpdateData(double value);
    void SetName(QString name);

private:
    QCPAxis *yAxis;
    QPointer<QCPItemText> labelMin;
    QPointer<QCPItemText> labelMax;
    QPointer<QCPItemText> labelName;

    double minValue, maxValue;
};

#endif // LABELS_H
