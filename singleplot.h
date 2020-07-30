#ifndef SINGLEPLOT_H
#define SINGLEPLOT_H

#include <QWidget>

#include "axistag.h"
#include "movingline.h"
#include "labels.h"
#include "systeminfo.h"

//class SinglePlot : public QCustomPlot
//{
//    Q_OBJECT
//public:
//    explicit SinglePlot(QCustomPlot *parent = nullptr);

//    bool CreateSingleChart(QString type);
//    void CreateAllCharts();
//    bool Contains(QString type);

//private slots:
//    void ContextMenu(const QPoint &pos);
//    void MouseEvent(QMouseEvent *event);
//    void TimerSlot();
//    void RemoveGraph();
//    int GetSuitRangeMin(int i);
//    int GetSuitYRange(int i);

//private:
//    enum TypesIndexes
//    {
//        VirtualMemoryCommited, VirtualMemoryAvailable, PhysicalMemoryUsed, PhysicalMemoryAvailable, PhysicalMemoryLoad
//    };

//    int quantity;
//    QStringList types;
//    QList <bool> exists;
//    QList <QPointer<QCPAxisRect>> rects;
//    QList <QPointer<QCPGraph>> graphs;
//    QList <Magic*> magics;
//    QList <UserExpProperties*> verticals;
//    QList <Labels*> labels;

//    SystemInfo sysInfo;

//    QTimer timer;
//};

#endif // SINGLEPLOT_H
