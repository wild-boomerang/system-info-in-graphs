#include "chartwindow.h"
#include "ui_chartwindow.h"

ChartWindow::ChartWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChartWindow)
{
    ui->setupUi(this);

    Plot *plot = new Plot();
    plot->CreateAllCharts();
    ui->scrollArea->setWidget(plot);
}

ChartWindow::~ChartWindow()
{
    delete ui;
}
