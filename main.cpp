#include <QApplication>
#include "mainwindow.h"
#include "manager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Manager m;
    MainWindow w(m);
    w.show();
    return a.exec();
}
