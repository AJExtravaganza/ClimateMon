#ifndef ARDUINOINTERFACE_H
#define ARDUINOINTERFACE_H

#include <QFile>
#include <QThread>
#include "datalogger.h"
#include "devicestatus.h"
#include "satellitedatum.h"

const int DEVICECOUNT = 6;

class ArduinoInterface : public QThread
{
private:
    const int TEMPHYSTERESIS; //In decidegC
    const int HUMHYSTERESIS; //In deci%RH
    void initialiseDatalogger(int deviceID);
    void parse(QString datastring); //Call update(), and other types of xmit-related functions
    void updateValues(QString datastring);
    Datalogger logger[DEVICECOUNT];
    QFile datalogs[DEVICECOUNT];

public:
    SatelliteDatum climateData[DEVICECOUNT];
    DeviceStatus deviceStatus[DEVICECOUNT];
    ArduinoInterface();
    void run(); //Initiates serial comms on a loop (thread)
};

#endif // ARDUINOINTERFACE_H
