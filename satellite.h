#ifndef SATELLITE_H
#define SATELLITE_H

#include "datalogger.h"
#include "satellitedatum.h"
#include "devicestatus.h"

const int USERTEMPHYSTERESIS = 1; //In decidegC
const int USERHUMHYSTERESIS = 5; //In deci%RH

class Satellite {
private:
    const int TEMPHYSTERESIS; //In decidegC
    const int HUMHYSTERESIS; //In deci%RH
    int deviceID;
    void initialiseDatalogger();
    //void parse(QString datastring); //Call update(), and other types of xmit-related functions
    Datalogger logger;
    QFile datalog;

public:
    SatelliteDatum climateData;
    DeviceStatus deviceStatus;
    Satellite();
    Satellite(int deviceID);
    void setDeviceID(int deviceID);
    void updateValues(unsigned long int secondsElapsed, int temperature, int humidity);
};

#endif // SATELLITE_H
