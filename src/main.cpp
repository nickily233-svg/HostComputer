#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QThread>

#include "src/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc,argv);

    qRegisterMetaType<DAQStatus>("DAQStatus");
    MainWindow window;

    window.show();

    return a.exec();
}
