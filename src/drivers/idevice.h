#ifndef IDEVICE_H
#define IDEVICE_H

#include <vector>
#include <string>
#include <cstdint>

// struct : Capture card status
struct DAQStatus {

    uint64_t actSampleRate;                  // Msps
    uint64_t samplesAcquired;                // the sample sum has been captured
    uint32_t overflowCount;                  // overflow counter
    bool isRunning;

};

// pure virtual base class
class IDevice
{

public:
    virtual ~IDevice() = default;
    virtual bool open() = 0;                               // open device
    virtual void close() = 0;                              // close device
    virtual bool configure(int channels,double sampleRate) = 0; // config device (chx SampleRate TriggerMode)
    virtual bool start() = 0;                              // start capture
    virtual void stop() = 0;                               // stop capture
    virtual std::vector<std::vector<double>> readBatch(size_t numSample,int timeoutMs) = 0; // double return value
                                                                                            // outside : channel
                                                                                            // inside : sample value
    virtual DAQStatus getStatus() = 0;                     // get status
};

#endif // IDEVICE_H
