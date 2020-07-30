#ifndef SINGLECHARTWINDOW_H
#define SINGLECHARTWINDOW_H

#include <QDialog>

#include "plot.h"

namespace Ui {
class SingleChartWindow;
}

class SingleChartWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SingleChartWindow(QString type, QWidget *parent = nullptr);
    ~SingleChartWindow();

private:
    Ui::SingleChartWindow *ui;
    Plot *plot;
};

#endif // SINGLECHARTWINDOW_H
