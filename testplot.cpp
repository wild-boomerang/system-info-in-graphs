#include "testplot.h"

TestPlot::TestPlot(QCustomPlot *parent) : QCustomPlot(parent)
{
    this->plotLayout()->clear();

//    plot->setContextMenuPolicy(Qt::CustomContextMenu);
//    connect(plot, &QCustomPlot::customContextMenuRequested, this, &MainWindow::ContextMenu);
    this->setInteractions(QCP::iRangeZoom | QCP::iRangeDrag);

//    plot->yAxis->setTickLabels(false);
//    connect(plot->yAxis2, SIGNAL(rangeChanged(QCPRange)), plot->yAxis, SLOT(setRange(QCPRange))); // left axis only mirrors inner right axis
//    plot->yAxis2->setVisible(true);
//    plot->axisRect()->axis(QCPAxis::atRight, 0)->setPadding(50); // add some padding to have space for tags

//    // create graphs:
//    graph1 = plot->addGraph(plot->xAxis, plot->axisRect()->axis(QCPAxis::atRight, 0));
//    graph1->setPen(QPen(QColor(250, 120, 0)));

//    // create tags with newly introduced AxisTag class (see axistag.h/.cpp):
//    magic1 = new Magic(graph1->valueAxis());
//    magic1->setPen(graph1->pen());

//    vertical = new UserExpProperties(graph1->valueAxis());
//    connect(plot, &QCustomPlot::mouseMove, this, &MainWindow::MouseEvent);

//    labels = new Labels(graph1->valueAxis());

//    connect(&timer, &QTimer::timeout, this, &MainWindow::TimerSlot);
//    timer.start(1000);


}

void TestPlot::TimerSlot()
{
    // calculate and add a new data point to each graph:
//    graph1->addData(graph1->dataCount(), double(GetCPULoad() * 100));
    graph1->addData(graph1->dataCount(), qSin(graph1->dataCount()/50.0)+qSin(graph1->dataCount()/50.0/0.3843)*0.25);

    // make key axis range scroll with the data:
    this->xAxis->rescale();
    graph1->rescaleValueAxis(false, true);
    this->xAxis->setRange(this->xAxis->range().upper, 100, Qt::AlignRight);

    // update the vertical axis tag positions and texts to match the rightmost data point of the graphs:
    double graph1Value = graph1->dataMainValue(graph1->dataCount() - 1);
    magic1->updatePosition(graph1Value);
    magic1->setText(QString::number(graph1Value, 'f', 2));

    vertical->timerUpdateSlot();
    labels->UpdateData(graph1Value);

    this->replot();
}

void TestPlot::MouseEvent(QMouseEvent *event)
{
    vertical->moveSlot(event);
    this->replot();
}

void TestPlot::ContextMenu(const QPoint &pos)
{
    QAction *clear = new QAction("Clear");
    QMenu *menu = new QMenu();

//    connect(clear, &QAction::triggered, this, &MainWindow::);

    menu->addAction(clear);
    menu->popup(this->mapToGlobal(pos));
}
