#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <modeldata.h>
#include <qcustomplot.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void on_textEdit_textChanged();

    void on_textEdit_cursorPositionChanged();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    void generategraph(QCustomPlot *customPlot,int max, double* func,double start, double end);
};

#endif // MAINWINDOW_H
