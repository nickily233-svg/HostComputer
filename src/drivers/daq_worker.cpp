#include "src/drivers/daq_worker.h"

DAQWorker::DAQWorker(IDevice *device,QObject *parent)
    : QObject(parent),
    isRunning(false),
    device(device)
{

}

DAQWorker::~DAQWorker()
{
    stopAcquisition();
}

void DAQWorker::startAcquisition()
{
    if(isRunning)
        return;

    isRunning = true;

    // 预分配 4KB 内存，避免每次循环都分配
    const quint64 BUFFER_SIZE = 4096;
    QByteArray rawBuffer(BUFFER_SIZE, 0);
    quint64 bytesRead = 0;

    qDebug() << "采集线程启动, 线程ID:" << QThread::currentThreadId();

    // 核心采集循环
    while (isRunning) {
        if (device->readRawData(rawBuffer.data(), BUFFER_SIZE, bytesRead, 100)) {
            emit dataReady(rawBuffer,bytesRead);
        }

        // 定期发送状态
        static int statusCounter = 0;
        // 每10次循环发一次状态
        if (++statusCounter >= 10) {
            emit statusUpdated(device->getStatus());
            statusCounter = 0;
        }
    }

    qDebug() << "采集线程退出";
}

void DAQWorker::stopAcquisition()
{
    isRunning = false;
}