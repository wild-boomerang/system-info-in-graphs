#ifndef PLOT_H
#define PLOT_H

#include <QWidget>

#include "axistag.h"
#include "movingline.h"
#include "labels.h"
#include "systeminfo.h"

using funcPointer = long (*)();

class Plot : public QCustomPlot
{
    Q_OBJECT
public:
    explicit Plot(QCustomPlot *parent = nullptr);

    bool CreateSingleChart(QString type);
    void CreateAllCharts();
    bool Contains(QString type);

    int getInterval() const;
    void setInterval(int value);

private slots:
    void ContextMenu(const QPoint &pos);
    void MouseEvent(QMouseEvent *event);
    void TimerSlot();
    void RemoveGraph();
    int GetSuitRangeMaxValue(int i);
    void StopMonitoring();
    void ContinueMon();

private:
    enum TypesIndexes
    {
        VirtualMemoryCommited, VirtualMemoryAvailable, PhysicalMemoryUsed, PhysicalMemoryAvailable, PhysicalMemoryLoad
    };

    int quantity, interval, activeIndex;
    QStringList types;
    QList <bool> exists;
    QList <QPointer<QCPAxisRect>> rects;
    QList <QPointer<QCPGraph>> graphs;
    QList <AxisTag*> magics;
    QList <MovingLine*> verticals;
    QList <Labels*> labels;

    SystemInfo sysInfo;

    QTimer timer;
};

#endif // PLOT_H
