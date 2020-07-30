#ifndef WIDGETCONTAINER_H
#define WIDGETCONTAINER_H

#include <QWidget>
#include <QScrollArea>
#include <QLabel>
#include <QVBoxLayout>
#include "plot.h"

class WidgetContainer : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetContainer(QWidget *parent = nullptr);

private:
    QWidget *widget;
    Plot *plot;
    QLabel *label1;
    QLabel *label2;
    QScrollArea *scrollArea;
    QVBoxLayout *verticalLayout;
};

#endif // WIDGETCONTAINER_H
