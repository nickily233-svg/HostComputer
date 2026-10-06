#ifndef MOCKDEVICE_H
#define MOCKDEVICE_H

#include "src/drivers/idevice.h"
#include <chrono>
#include <random>

#ifndef PI
#define PI 3.14159265358979323846
#endif

class MockDevice : public IDevice
{
public :
    MockDevice();
    ~MockDevice() override;

    // 实现 IDevice 的纯虚接口
    bool open() override;
    void close() override;
    bool configure(const DAQConfig &config) override;
    DAQConfig getConfig() const override;
    DAQStatus getStatus() const override;
    bool start() override;
    void stop() override;

    // 核心 直接写入预分配的原始内存块
    bool readRawData(void *buffer,size_t bufferSize,size_t &bytesRead,int timeoutMs) override;

    std::string getError() const override;

private :
    bool isOpen;
    bool isRunning;

    DAQStatus status;
    DAQConfig config;

    // 产生平滑连续的模拟数据
    double timeOffset;
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;

    // 随机数生成器 用于添加底噪
    std::mt19937 gen;
    std::uniform_real_distribution<double> noiseDist;

    std::string Error;
};


#endif // MOCKDEVICE_H