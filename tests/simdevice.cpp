#include "simdevice.h"
#include <QDebug>

/*
 * Parsing function
 */
Simdevice::Simdevice()
    : m_isRunning(false),
      m_channels(4),
      m_sampleCounter(0),
      m_sampleRate(1000)

{

    m_phases.resize(m_channels,0);

}

/*
 * Destruct function
 */
Simdevice::~Simdevice() {

}

/*
 * open device
 */
bool Simdevice::open() {

    qDebug() << "[simDevice] open";
    return true;

};

/*
 * close device
 */
void Simdevice::close() {

    qDebug() << "[simDevice] close";

};

/*
 * configure device
 */
bool Simdevice::configure(int channels,double sampleRate) {

    m_sampleRate = sampleRate;
    m_channels = channels;
    m_phases.resize(channels,0);
    qDebug() << "[simDevice] configure : channels = " << channels << "sampleRate = " << sampleRate;
    return true;
};

/*
 * start device
 */
bool Simdevice::start() {

    m_isRunning = true;
    m_sampleCounter = 0;
    qDebug() << "[simDevice] start";
    return true;

};

/*
 * stop device
 */
void Simdevice::stop() {

    m_isRunning = false;
    qDebug() << "[simDevice] stop";

};

/*
 * read batch
 */
std::vector<std::vector<double>> Simdevice::readBatch(size_t numSample,int timeoutMs) {

    std::vector<std::vector<double>> batch(m_channels,std::vector<double>(numSample,0));
    size_t i;
    uint8_t ch;

    if(!m_isRunning)
        return batch;

    const double PI = 3.14159265358979323846;

    for(i = 0;i < numSample;i++) {

        double t = static_cast<double>(m_sampleCounter) / static_cast<double>(m_sampleRate);

        for(ch = 0;ch < m_channels;ch++) {
            batch[ch][i] = (ch + 1.0) * std::sin(2.0 * PI * 1.0 * t + m_phases[ch]);
        }
    m_sampleCounter++;
    qDebug() << "ch =" << ch << "m_sampleCounter =" << m_sampleCounter << "m_sampleRate =" <<m_sampleRate;
    }

    return batch;
};

/*
 * get device's status
 */
DAQStatus Simdevice::getStatus() {

    DAQStatus status;

    status.isRunning = m_isRunning;
    status.actSampleRate = m_sampleRate;
    status.samplesAcquired = m_sampleCounter;
    status.overflowCount = 0;

    return status;

};
