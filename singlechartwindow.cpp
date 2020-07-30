#include "singlechartwindow.h"
#include "ui_singlechartwindow.h"

#include <QDebug>

SingleChartWindow::SingleChartWindow(QString type, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SingleChartWindow)
{
    ui->setupUi(this);
    plot = new Plot();
    plot->CreateSingleChart(type);
    ui->scrollArea->setWidget(plot);
}

SingleChartWindow::~SingleChartWindow()
{
    delete ui;
}
