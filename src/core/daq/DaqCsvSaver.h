#ifndef DAQCSVSAVER_H
#define DAQCSVSAVER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QMutex>
#include <QQueue>

class DAQCSVSaver : public QObject
{

    Q_OBJECT

public :
    explicit DAQCSVSaver(QObject *parent = nullptr);
    ~DAQCSVSaver();

public slots:

private :

};


#endif // DAQCSVSAVER_H