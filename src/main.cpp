#include "hostcomputer.h"

#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QThread>
#include "src/drivers/simdevice.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc,argv);
    uint8_t i;
    uint8_t ch;

    Simdevice sim;
    sim.open();
    sim.configure(4,1000);
    sim.start();

    for(i = 0;i < 10;i++) {
        std::vector<std::vector<double>> data = sim.readBatch(10, 1);
        for(ch = 0;ch < 4;ch++) {
            qDebug() << "  通道" << ch << ":"
                    << QString::number(data[ch][0], 'f', 10) << ","
                    << QString::number(data[ch][1], 'f', 10) << ","
                    << QString::number(data[ch][2], 'f', 10) << ","
                    << QString::number(data[ch][3], 'f', 10);
        }
        QThread::msleep(10);
    }

    sim.stop();
    sim.close();

    return 0;
}
