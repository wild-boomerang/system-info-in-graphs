#include "plot.h"

Plot::Plot(QCustomPlot *parent) : QCustomPlot(parent)
{
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QCustomPlot::customContextMenuRequested, this, &Plot::ContextMenu);
    this->setInteractions(QCP::iRangeZoom | QCP::iRangeDrag);
    this->plotLayout()->clear();
//    this->setBackground(QBrush(Qt::darkGray));

    types.append("Virtual Memory Commited");
    types.append("Virtual Memory Available");
    types.append("Physical Memory Used");
    types.append("Physical Memory Available");
    types.append("Physical Memory Load");
    types.append("Total CPU Usage");

    quantity = 6;
    interval = 100;

    for (int i = 0; i < quantity; i++)
        exists.append(false);
}

bool Plot::CreateSingleChart(QString type)
{
    if (types.contains(type))
    {
        exists[types.indexOf(type)] = true;
//        activeIndex = types.indexOf(type);

        // Rect
        QCPAxisRect *rect = new QCPAxisRect(this);
        rect->axis(QCPAxis::atLeft)->setTickLabels(false);
        connect(rect->axis(QCPAxis::atRight), SIGNAL(rangeChanged(QCPRange)), rect->axis(QCPAxis::atLeft), SLOT(setRange(QCPRange)));
        rect->axis(QCPAxis::atRight)->setVisible(true);
        rect->axis(QCPAxis::atRight, 0)->setPadding(50);
        this->plotLayout()->addElement(0, 0, rect);
        rect->setMinimumSize(QSize(370, 200));
        rect->axis(QCPAxis::atRight)->setRange(0, this->GetSuitRangeMaxValue(types.indexOf(type)));
        rects.append(rect);

        // Graph
        QCPGraph *graph = this->addGraph(rect->axis(QCPAxis::atBottom), rect->axis(QCPAxis::atRight));
        graph->setPen(QPen(QColor(250, 120, 0)));
        graphs.append(graph);

        // AxisTag
        AxisTag *magic = new AxisTag(graph->valueAxis());
        magic->setPen(graph->pen());
        magics.append(magic);

        // MovingLine
        MovingLine *vertical = new MovingLine(graph->valueAxis());
        verticals.append(vertical);

        // Labels
        Labels *label = new Labels(graph->valueAxis());
        label->SetName(type);
        labels.append(label);

        connect(this, &QCustomPlot::mouseMove, this, &Plot::MouseEvent);
        connect(&timer, &QTimer::timeout, this, &Plot::TimerSlot);
        timer.start(interval);

        return true;
    }

    return false;
}

void Plot::CreateAllCharts()
{
    for (int i = 0; i < quantity; i++)
    {
        exists[i] = true;

        // Rect
        QCPAxisRect *rect = new QCPAxisRect(this);
        rect->axis(QCPAxis::atLeft)->setTickLabels(false);
        connect(rect->axis(QCPAxis::atRight), SIGNAL(rangeChanged(QCPRange)), rect->axis(QCPAxis::atLeft), SLOT(setRange(QCPRange)));
        rect->axis(QCPAxis::atRight)->setVisible(true);
        rect->axis(QCPAxis::atRight, 0)->setPadding(50);
        this->plotLayout()->addElement(i, 0, rect);
        rect->setMinimumSize(QSize(370, 200));
        rect->axis(QCPAxis::atRight)->setRange(0, this->GetSuitRangeMaxValue(i));
        rects.append(rect);

        // Graph
        QCPGraph *graph = this->addGraph(rect->axis(QCPAxis::atBottom), rect->axis(QCPAxis::atRight));
        graph->setPen(QPen(QColor(250, 120, 0)));
        graphs.append(graph);

        // AxisTag
        AxisTag *magic = new AxisTag(graph->valueAxis());
        magic->setPen(graph->pen());
        magics.append(magic);

        // MovingLine
        MovingLine *vertical = new MovingLine(graph->valueAxis());
        verticals.append(vertical);

        // Labels
        Labels *label = new Labels(graph->valueAxis());
        label->SetName(types[i]);
        labels.append(label);
    }

    connect(this, &QCustomPlot::mouseMove, this, &Plot::MouseEvent);
    connect(&timer, &QTimer::timeout, this, &Plot::TimerSlot);
    timer.start(interval);
}

bool Plot::Contains(QString type)
{
    return types.contains(type);
}

void Plot::TimerSlot()
{
////    graph1->addData(graph1->dataCount(), double(GetCPULoad() * 100));

    long (*funcPointer[])() = { SystemInfo::GetVirtualMemoryCommited, SystemInfo::GetVirtualMemoryAvailable,
                                SystemInfo::GetPhysicalMemoryUsed, SystemInfo::GetPhysicalMemoryAvailable,
                                SystemInfo::GetPhysicalMemoryLoad, SystemInfo::GetCPULoad };


    for (int i = 0; i < rects.size(); i++)
    {
        if (rects.size() == 1)
        {
//            graphs[activeIndex]->addData(graphs[i]->dataCount(), (*funcPointer[j])());
            for (int j = 0; j < exists.size(); j++)
                if (exists[j])
                    graphs[i]->addData(graphs[i]->dataCount(), (*funcPointer[j])());
        }

        else
            graphs[i]->addData(graphs[i]->dataCount(), (*funcPointer[i])()/*qSin(graphs[i]->dataCount()/50.0)+qSin(graph2->dataCount()/50.0/0.3843)*0.25*/);

        // make key axis range scroll with the data:
        rects[i]->axis(QCPAxis::atBottom)->rescale();
//        graphs[i]->rescaleValueAxis(false, true);
        rects[i]->axis(QCPAxis::atBottom)->setRange(rects[i]->axis(QCPAxis::atBottom)->range().upper, 100, Qt::AlignRight);

        // update the vertical axis tag positions and texts to match the rightmost data point of the graphs:
        double graphValue = graphs[i]->dataMainValue(graphs[i]->dataCount() - 1);
        magics[i]->updatePosition(graphValue);
        magics[i]->setText(QString::number(graphValue/*, 'f', 2*/));

        verticals[i]->timerUpdateSlot();
        labels[i]->UpdateData(graphValue);
    }

    this->replot();
}

void Plot::RemoveGraph()
{
//    this->plotLayout()->removeAt(1);
//    this->removeGraph(this->selectedGraphs()[0]);
}

int Plot::GetSuitRangeMaxValue(int i)
{
    switch (i)
    {
    case 0:
    case 1:
        return SystemInfo::GetVirtualTotal();
        break;
    case 2:
    case 3:
        return SystemInfo::GetPhysicalTotal();
        break;
    case 4:
    case 5:
        return 100;
        break;
    default:
        return 0;
    }
}

void Plot::StopMonitoring()
{
//    if (timer.isActive())
        timer.stop();
//    else
//        timer.start(interval);
}

void Plot::ContinueMon()
{
    timer.start(interval);
}

int Plot::getInterval() const
{
    return interval;
}

void Plot::setInterval(int value)
{
    interval = value;
}

void Plot::MouseEvent(QMouseEvent *event)
{
    for (int i = 0; i < verticals.size(); i++)
    {
        verticals[i]->moveSlot(event);
    }

    this->replot();
}

void Plot::ContextMenu(const QPoint &pos)
{
    QAction *clear = new QAction("Stop");
    QAction *continueMon = new QAction("Continue");
//    QAction *remove = new QAction("Remove the graph");
    QMenu *menu = new QMenu();
//    connect(clear, &QAction::triggered, this, &Plot::ClearGraph);
    connect(clear, &QAction::triggered, this, &Plot::StopMonitoring);
    connect(continueMon, &QAction::triggered, this, &Plot::ContinueMon);
//    connect(remove, &QAction::triggered, this, &Plot::RemoveGraph);

    menu->addAction(clear);
    menu->addAction(continueMon);
    menu->popup(this->mapToGlobal(pos));
}

//    for (int i = 0; i < 5; i++)
//        graphs[i]->addData(graphs[i]->dataCount(), (*funcPointer[i])());

//    graphs[5]->addData(graphs[5]->dataCount(), double(SystemInfo::GetCPULoad()));

//    if (rects.size() > 1)
//    {
//        if (exists[0])
//            graphs[0]->addData(graphs[0]->dataCount(), SystemInfo::GetVirtualMemoryCommited());
//        if (exists[1])
//            graphs[1]->addData(graphs[1]->dataCount(), SystemInfo::GetVirtualMemoryAvailable());
//        if (exists[2])
//            graphs[2]->addData(graphs[2]->dataCount(), SystemInfo::GetPhysicalMemoryUsed());
//        if (exists[3])
//            graphs[3]->addData(graphs[3]->dataCount(), SystemInfo::GetPhysicalMemoryAvailable());
//        if (exists[4])
//            graphs[4]->addData(graphs[4]->dataCount(), SystemInfo::GetPhysicalMemoryLoad());
//        if (exists[5])
//            graphs[5]->addData(graphs[5]->dataCount(), double(SystemInfo::GetCPULoad()));
//    }

//    else
//    {
//        if (exists[0])
//            graphs[0]->addData(graphs[0]->dataCount(), SystemInfo::GetVirtualMemoryCommited());
//        if (exists[1])
//            graphs[0]->addData(graphs[0]->dataCount(), SystemInfo::GetVirtualMemoryAvailable());
//        if (exists[2])
//            graphs[0]->addData(graphs[0]->dataCount(), SystemInfo::GetPhysicalMemoryUsed());
//        if (exists[3])
//            graphs[0]->addData(graphs[0]->dataCount(), SystemInfo::GetPhysicalMemoryAvailable());
//        if (exists[4])
//            graphs[0]->addData(graphs[0]->dataCount(), SystemInfo::GetPhysicalMemoryLoad());
//        if (exists[5])
//            graphs[0]->addData(graphs[0]->dataCount(), double(SystemInfo::GetCPULoad()));
//    }
