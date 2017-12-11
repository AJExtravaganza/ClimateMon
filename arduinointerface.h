#ifndef ARDUINOINTERFACE_H
#define ARDUINOINTERFACE_H

#include <QFile>
#include <QThread>
#include "datalogger.h"
#include "satellitedatum.h"

const int DEVICECOUNT = 6;

class ArduinoInterface : public QThread
{
private:
    bool liveDevices[DEVICECOUNT]; //Curently unused
    void update(QString datastring);
    Datalogger logger[DEVICECOUNT];
    QFile datalogs[DEVICECOUNT];

public:
    SatelliteDatum climateData[DEVICECOUNT];
    ArduinoInterface();
    void run(); //Initiates serial comms on a loop (thread)
};

#endif // ARDUINOINTERFACE_H
