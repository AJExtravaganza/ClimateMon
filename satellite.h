#ifndef SATELLITE_H
#define SATELLITE_H



class Satellite {
private:
    const int TEMPHYSTERESIS; //In decidegC
    const int HUMHYSTERESIS; //In deci%RH
    int deviceID;
    void initialiseDatalogger();
    //void parse(QString datastring); //Call update(), and other types of xmit-related functions
    void updateValues(unsigned long int secondsElapsed, int temperature, int humidity);
    Datalogger logger;
    QFile datalog;

public:
    SatelliteDatum climateData;
    DeviceStatus deviceStatus;
    Satellite();
    Satellite(int deviceID);
};

#endif // SATELLITE_H
