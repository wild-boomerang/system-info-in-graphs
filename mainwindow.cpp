#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);    

    plot = new Plot();
    stopWatch = new QTime(0, 0);
    stopWatchHelper.start(1000);
    connect(&stopWatchHelper, &QTimer::timeout, this, &MainWindow::StopWatchUpdate);    

    ui->tableWidgetMain->setColumnCount(2);
    QStringList horHeaders;
    horHeaders << "Sensor" << "Values";
    ui->tableWidgetMain->setHorizontalHeaderLabels(horHeaders);
    ui->tableWidgetMain->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetMain->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tableWidgetMain->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetMain->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetMain->setColumnWidth(0, 700);

    ui->tableWidgetMain->setRowCount(9);
    ui->tableWidgetMain->setItem(0, 0, new QTableWidgetItem("Memory"));
    ui->tableWidgetMain->setItem(0, 1, new QTableWidgetItem);
    ui->tableWidgetMain->setItem(6, 0, new QTableWidgetItem);
    ui->tableWidgetMain->setItem(6, 1, new QTableWidgetItem);
    ui->tableWidgetMain->setItem(7, 0, new QTableWidgetItem("CPU"));
    ui->tableWidgetMain->setItem(7, 1, new QTableWidgetItem);

    TimerSlot();

    connect(&timer, &QTimer::timeout, this, &MainWindow::TimerSlot);
    timer.start(plot->getInterval());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::TimerSlot()
{
    ui->tableWidgetMain->setItem(1, 0, new QTableWidgetItem("Virtual Memory Commited"));
    ui->tableWidgetMain->setItem(1, 1, new QTableWidgetItem(QString::number(SystemInfo::GetVirtualMemoryCommited())));

    ui->tableWidgetMain->setItem(2, 0, new QTableWidgetItem("Virtual Memory Available"));
    ui->tableWidgetMain->setItem(2, 1, new QTableWidgetItem(QString::number(SystemInfo::GetVirtualMemoryAvailable()) + "MB"));

    ui->tableWidgetMain->setItem(3, 0, new QTableWidgetItem("Physical Memory Used"));
    ui->tableWidgetMain->setItem(3, 1, new QTableWidgetItem(QString::number(SystemInfo::GetPhysicalMemoryUsed()) + "MB"));

    ui->tableWidgetMain->setItem(4, 0, new QTableWidgetItem("Physical Memory Available"));
    ui->tableWidgetMain->setItem(4, 1, new QTableWidgetItem(QString::number(SystemInfo::GetPhysicalMemoryAvailable()) + "MB"));

    ui->tableWidgetMain->setItem(5, 0, new QTableWidgetItem("Physical Memory Load"));
    ui->tableWidgetMain->setItem(5, 1, new QTableWidgetItem(QString::number(SystemInfo::GetPhysicalMemoryLoad()) + "%"));

    ui->tableWidgetMain->setItem(8, 0, new QTableWidgetItem("Total CPU Usage"));
    ui->tableWidgetMain->setItem(8, 1, new QTableWidgetItem(QString::number(double(SystemInfo::GetCPULoad())) + "%"));

//    ui->tableWidgetMain->resizeColumnsToContents();
}

void MainWindow::on_tableWidgetMain_customContextMenuRequested(const QPoint &pos)
{
    QAction *showAllCharts = new QAction("Show all charts");
    QMenu *menu = new QMenu();

    connect(showAllCharts, &QAction::triggered, this, &MainWindow::ShowAllCharts);

    menu->addAction(showAllCharts);
    menu->popup(ui->tableWidgetMain->viewport()->mapToGlobal(pos));
}

void MainWindow::ShowAllCharts()
{
    ChartWindow *charts = new ChartWindow();
    charts->show();
}

void MainWindow::StopWatchUpdate()
{
    *stopWatch = stopWatch->addSecs(1);
    ui->statusBar->showMessage(stopWatch->toString());
}

void MainWindow::on_tableWidgetMain_cellDoubleClicked(int row, int column)
{
    if (!plot->Contains(ui->tableWidgetMain->item(row, 0)->text()))
        return;

    SingleChartWindow *window = new SingleChartWindow(ui->tableWidgetMain->item(row, 0)->text());
    window->exec();

    Q_UNUSED(column);
}
