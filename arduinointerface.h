#ifndef ARDUINOINTERFACE_H
#define ARDUINOINTERFACE_H

#include <QThread>
#include "satellite.h"

const int DEVICECOUNT = 6;

class ArduinoInterface : public QThread
{
private:
    //const int TEMPHYSTERESIS; //In decidegC
    //const int HUMHYSTERESIS; //In deci%RH
    //void initialiseDatalogger(int deviceID);
    void parseTransmission(QString datastring); //Call update(), and other types of xmit-related functions
    void parseValuesToSatellite(QString datastring);
    //Datalogger logger[DEVICECOUNT];
    //QFile datalogs[DEVICECOUNT];

public:
    Satellite fieldDevice[DEVICECOUNT]; // element 0 is not used and exists so no index offset is necessary in code.
    //SatelliteDatum climateData[DEVICECOUNT];
    //DeviceStatus deviceStatus[DEVICECOUNT];
    ArduinoInterface();
    void run(); //Initiates serial comms on a loop (thread)
};

#endif // ARDUINOINTERFACE_H
