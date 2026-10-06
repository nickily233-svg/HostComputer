#include <src/drivers/mock_device.h>
#include <cmath>
#include <thread>
#include <algorithm>
#include <iostream>

MockDevice::MockDevice()
    : isOpen(false),
    isRunning(false),
    timeOffset(0.0),
    gen(std::random_device{}()),
    noiseDist(-0.05,0.05)
{
    config.channels = 4;
    config.bitDepth = 16;
    config.isInterleaved = true;
    config.sampleRate = 1000.0;
    config.triggerMode = 0;

    status = {0,0,0,0,false};
}

MockDevice::~MockDevice()
{
    close();
}

bool MockDevice::open()
{
    if(isOpen)
        return true;
    isOpen = true;
    isRunning = false;
    status = {0,0,0,0,false};
    return true;
}

void MockDevice::close()
{
    stop();
    isOpen = false;
}

bool MockDevice::configure(const DAQConfig &import_config)
{
    if(!isOpen) {
        Error = "Device is not Open.";
        return false;
    } else if(config.channels <= 0 || config.sampleRate <= 0) {
        Error = "Invaild configuration parameters.";
        return false;
    }

    config = import_config;
    return true;
}

DAQConfig MockDevice::getConfig() const
{
    return config;
}

DAQStatus MockDevice::getStatus() const
{

    return status;
}

bool MockDevice::start()
{
    if(!isOpen) {
        Error = "Device is not Open.";
        return false;
    } else {
        isRunning = true;
        status.sampleAcquired = 0;
        status.overflowCount = 0;
        status.isRunning = true;
        status.byteAcquired = 0;
        timeOffset = 0.0f;
        startTime = std::chrono::high_resolution_clock::now();
        return true;
    }

    return true;
}

void MockDevice::stop()
{
    isRunning = false;
    status.isRunning = false;
}

bool MockDevice::readRawData(void *buffer,size_t bufferSize,size_t &bytesRead,int timeoutMs)
{
    bytesRead = 0;
    if(!isRunning | !isOpen) {
        Error = "Device is not running or not open.";
        return false;
    }

    // 模拟硬件阻塞延迟
    // 真实硬件会在此处等待 DMA 完成
    if(timeoutMs >= 0) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    // 计算缓冲区能够容纳多少样本
    size_t totalSamples = bufferSize / sizeof(int16_t);
    size_t samplePerChannel = totalSamples / config.channels;

    if(samplePerChannel == 0) {
        Error = "Bufer size is too small.";
        return false;
    }

    // 强制转为 int16_t p 模拟直接向内存写入数据
    int16_t *ptr = static_cast<int16_t *>(buffer);
    double dt = 1.0 / config.sampleRate;

    for(size_t i = 0;i < samplePerChannel;++i) {
        double currentTime = timeOffset + i * dt;

        for(int ch = 0;ch < config.channels;++ch) {
            // 模拟不同通道的正弦波:100Hz, 200Hz, 300Hz, 400Hz
            double frequency = 100.0 * (ch + 1);
            double amplitude = 1.0 + ch * 0.2;

            double signal = amplitude * std::sin(2.0 * PI * frequency * currentTime);
            // 添加底噪
            signal += noiseDist(gen);
            //模拟真实 ADC 的整数量化
            int16_t adcValue = static_cast<int16_t>(signal * 20000.0);
            *ptr++ = adcValue;
        }
    }

    // 更新状态
    bytesRead = samplePerChannel * config.channels * sizeof(int16_t);
    timeOffset += samplePerChannel * dt;
    status.sampleAcquired += samplePerChannel;
    status.byteAcquired += bytesRead;

    // 模拟偶尔发生一次溢出（概率极低），用于测试上位机的容错逻辑
    if (gen() % 10000 == 0) {
        status.overflowCount++;
    }

    return true;
}

std::string MockDevice::getError() const
{
    return Error;
}