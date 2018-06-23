#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowIcon(QIcon(":matlab.png"));
    w.setWindowTitle(QString("MiniMatlab"));
    w.show();

    return a.exec();
}
