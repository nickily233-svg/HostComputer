#ifndef SIMDEVICE_H
#define SIMDEVICE_H

#include <cstddef>
#include <cmath>
#include "idevice.h"

class Simdevice : public IDevice
{

public:

    Simdevice();
    ~Simdevice() override;

    virtual bool open() override;
    virtual void close() override;
    virtual bool configure(int channels,double sampleRate) override;
    virtual bool start() override;
    virtual void stop() override;
    virtual std::vector<std::vector<double>> readBatch(size_t numSample,int timeoutMs) override;
    virtual DAQStatus getStatus() override;

private :

    bool m_isRunning;
    int m_channels;
    uint64_t m_sampleCounter;
    uint64_t m_sampleRate;

    std::vector<uint64_t> m_phases;            // simulate phase
};

#endif // SIMDEVICE_H
