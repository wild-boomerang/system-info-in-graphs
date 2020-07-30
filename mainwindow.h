#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "chartwindow.h"
#include "singlechartwindow.h"
#include "axistag.h"
#include "movingline.h"
#include "labels.h"
#include "plot.h"
#include "systeminfo.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void TimerSlot();
    void ShowAllCharts();
    void StopWatchUpdate();

    void on_tableWidgetMain_customContextMenuRequested(const QPoint &pos);

    void on_tableWidgetMain_cellDoubleClicked(int row, int column);

private:
    Ui::MainWindow *ui;

    Plot *plot;
    QTimer timer;
    QTime *stopWatch;
    QTimer stopWatchHelper;
};

#endif // MAINWINDOW_H
