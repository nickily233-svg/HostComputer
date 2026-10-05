#ifndef IDEVICE_H
#define IDEVICE_H

#include <string>
#include <cstdint>

// 设备配置参数
struct DAQConfig {
    int channels; //通道数
    double sampleRate; // 采样率 Hz
    int bitDepth; // 位深 (8 12 16 bit)
    bool isInterleaved; // 数据是否交织
    int triggerMode; // 触发模式
};

struct DAQStatus {
    uint64_t actualSampleRate; // 实际采样率
    uint64_t sampleAcquired; // 已采集的总样本数(每通道)
    uint64_t byteAcquired; // 已采集的总字节数(用于底层流量统计)
    uint32_t overflowCount; // 溢出计数
    bool isRunning; // 是否正在运行
};

// 纯虚基类（通用接口）
class IDevice
{

public:
    virtual ~IDevice() = default;

    // 设定生命周期
    virtual bool open() = 0; // 打开设备
    virtual void close() = 0; // 关闭设备

    //配置与状态
    virtual bool configuare(const DAQConfig &config) = 0; // 配置设备参数
    virtual DAQConfig getConfig() const = 0; // 获取当前配置
    virtual DAQStatus getStatus() const = 0; // 获取当前状态

    // 采集控制
    virtual bool start() = 0; // 开始采集
    virtual void stop() = 0; // 停止采集

    /* 读取原始数据
     * @param1 : 外部提前分配好的大块内存
     * @param2 : 缓冲区的最大字节数
     * @param3 : 实际读取到的字节数
     * @param4 : 超时时间(Ms) -1:无限等待 0:非阻塞等待
     */
    virtual bool readRawDate(void *buffer,size_t bufferSize,size_t &bytesRead,int timeoutMs) = 0;

    // 错误处理（通用）
    virtual std::string getLastError() const = 0;
};

#endif // IDEVICE_H
