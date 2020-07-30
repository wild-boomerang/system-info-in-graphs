#include "widgetcontainer.h"

WidgetContainer::WidgetContainer(QWidget *parent) : QWidget(parent)
{
    QImage image("image-a2447871-1250x620w.jpg");

    label1 = new QLabel();
    label1->setPixmap(QPixmap::fromImage(image));

    label2 = new QLabel();
    label2->setPixmap(QPixmap::fromImage(image));

    plot = new Plot();
    QCustomPlot *testPlot = new QCustomPlot();

    verticalLayout = new QVBoxLayout();
    verticalLayout->addWidget(testPlot);
    verticalLayout->addWidget(plot);
    verticalLayout->addWidget(label1);
//    verticalLayout->addWidget(label2);

    widget = new QWidget();
    widget->setLayout(verticalLayout);

    scrollArea = new QScrollArea(this);
    scrollArea->setWidget(widget);
//    scrollArea->resize(500, 50);
}
