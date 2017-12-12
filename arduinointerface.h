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
    const int HYSTERESIS; //In decidegC or deci%RH
    bool liveDevices[DEVICECOUNT]; //Curently unused
    void initialiseDatalogger(int deviceID);
    void parse(QString datastring); //Call update(), and other types of xmit-related functions
    void update(QString datastring);
    Datalogger logger[DEVICECOUNT];
    QFile datalogs[DEVICECOUNT];

public:
    SatelliteDatum climateData[DEVICECOUNT];
    ArduinoInterface();
    void run(); //Initiates serial comms on a loop (thread)
};

#endif // ARDUINOINTERFACE_H
