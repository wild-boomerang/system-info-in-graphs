#include "singleplot.h"

//SinglePlot::SinglePlot(QCustomPlot *parent) : QCustomPlot(parent)
//{
//    // Rect
//    QCPAxisRect *rect = new QCPAxisRect(this);
//    rect->axis(QCPAxis::atLeft)->setTickLabels(false);
//    connect(rect->axis(QCPAxis::atRight), SIGNAL(rangeChanged(QCPRange)), rect->axis(QCPAxis::atLeft), SLOT(setRange(QCPRange)));
//    rect->axis(QCPAxis::atRight)->setVisible(true);
//    rect->axis(QCPAxis::atRight, 0)->setPadding(50);
//    this->plotLayout()->addElement(0, 0, rect);
//    rect->setMinimumSize(QSize(370, 200));
////    rect->axis(QCPAxis::atRight)->setRange(0, this->GetSuitRangeMin(types.indexOf(type)));
//    rects.append(rect);

//    // Graph
//    QCPGraph *graph = this->addGraph(rect->axis(QCPAxis::atBottom), rect->axis(QCPAxis::atRight));
//    graph->setPen(QPen(QColor(250, 120, 0)));
//    graphs.append(graph);

//    // Magic
//    Magic *magic = new Magic(graph->valueAxis());
//    magic->setPen(graph->pen());
//    magics.append(magic);

//    // Vertical
//    UserExpProperties *vertical = new UserExpProperties(graph->valueAxis());
//    verticals.append(vertical);

//    // Labels
//    Labels *label = new Labels(graph->valueAxis());
//    label->SetName(type);
//    labels.append(label);

//    connect(this, &QCustomPlot::mouseMove, this, &Plot::MouseEvent);
//    connect(&timer, &QTimer::timeout, this, &Plot::TimerSlot);
//    timer.start(100);
//}
