#ifndef DAQ_WORKER_H
#define DAQ_WORKER_H

#include <QObject>
#include <atomic>
#include <QThread>
#include <QDebug>
#include "src/drivers/idevice.h"
#include "src/drivers/mock_device.h"

class DAQWorker : public QObject
{
    Q_OBJECT

public :
    explicit DAQWorker(IDevice *device,QObject *parent = nullptr);
    ~DAQWorker();

public slots :
    // 开始采集
    void startAcquisition();
    // 停止采集
    void stopAcquisition();

signals :
    // 将原始数据块发给主线程
    void dataReady(const QByteArray &rawData,quint64 bytesRead);
    void statusUpdated(const DAQStatus &status);

private :
    IDevice *device;
    // 原子变量 保证线程安全
    std::atomic<bool> isRunning;
};

#endif // DAQ_WORKER_H