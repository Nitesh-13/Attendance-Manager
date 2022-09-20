#include "mainwindow.h"
#include "genlog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GENLOG::initLogging();
    MainWindow w;
    w.show();
    return a.exec();
}
