#ifndef ARDUINOINTERFACE_H
#define ARDUINOINTERFACE_H

#include <QThread>
#include <QSound>
#include <QDir>
#include "satellite.h"

const int DEVICECOUNT = 6;

class ArduinoInterface : public QThread
{
private:
    void parseTransmission(QString datastring); //Call update(), and other types of xmit-related functions
    void parseValuesToSatellite(QString datastring);

public:
    Satellite fieldDevice[DEVICECOUNT]; // element 0 is not used and exists so no index offset is necessary in code.
    QDir alarmToneFile;
    QSound alarmTone;
    ArduinoInterface();
    void run(); //Initiates serial comms on a loop (thread)
    //void clearAlarms(); //Implement later, may need to make ArdInt a QObject, but is this compatible with thread?
};

#endif // ARDUINOINTERFACE_H
