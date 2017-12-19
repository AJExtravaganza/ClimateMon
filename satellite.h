#ifndef SATELLITE_H
#define SATELLITE_H


class Satellite :
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

#endif // SATELLITE_H
