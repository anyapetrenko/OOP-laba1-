#include "mainwindow.h"
#include <QApplication>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(500,400);
    w.setWindowTitle("Timer Application");
    w.show();
  //  QTimer::singleShot(5000, &w, SLOT(close()));


    return a.exec();
}
