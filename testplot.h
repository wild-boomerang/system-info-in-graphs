#ifndef TESTPLOT_H
#define TESTPLOT_H

#include <QObject>

#include "magic.h"
#include "userexpproperties.h"
#include "labels.h"

class TestPlot : public QCustomPlot
{
public:
    explicit TestPlot(QCustomPlot *parent = nullptr);

private slots:
    void ContextMenu(const QPoint &pos);
    void MouseEvent(QMouseEvent *event);
    void TimerSlot();

private:
    QPointer<QCPGraph> graph1;
//    QPointer<QCPGraph> graph2;
    Magic *magic1;
//    Magic *magic2;
    UserExpProperties *vertical;
    Labels *labels;

    QTimer timer;
};

#endif // TESTPLOT_H
