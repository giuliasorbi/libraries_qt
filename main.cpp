#include <QApplication>
#include "mainwindow.h"
#include "datamanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Manager m;
    MainWindow w;
    w.show();
    return a.exec();
}
