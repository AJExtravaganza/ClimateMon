#ifndef SERIALLINK_H
#define SERIALLINK_H

#include <QFile>
#include <QThread>
#include "satellitedatum.h"

const int DEVICECOUNT = 6;

class ArduinoInterface : public QThread
{
private:
    bool liveDevices[DEVICECOUNT]; //Curently unused
    void update(QString datastring);
    QFile datalogs[DEVICECOUNT];

public:
    SatelliteDatum climateData[DEVICECOUNT];
    ArduinoInterface();
    void run();
};

#endif // SERIALLINK_H
