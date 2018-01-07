#include "arduinointerface.h"
#include <qdebug.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QDate>
#include <QTime>
#include "SerialPort.h"

using std::cout;
using std::endl;

ArduinoInterface::ArduinoInterface() : alarmToneFile("alarmshort.wav"), alarmTone(alarmToneFile.absolutePath())
{
    alarmTone.setLoops(alarmTone.Infinite);

    for (int i = 1; i < DEVICECOUNT; i++) {
        fieldDevice[i].setDeviceID(i);
        fieldDevice[i].deviceStatus.setValue(true);
    }
}

void ArduinoInterface::run() {

    /*Portname must contain these backslashes, and remember to
    replace the following com port*/
    QString port_name = "\\\\.\\COM4";

    //String for incoming data
    char incomingData[MAX_DATA_LENGTH];
    QString dataString = "";

    SerialPort arduino(port_name);
      if (arduino.isConnected()) {
          qDebug() << "Connection Established" << endl;
      }
      else {
          qDebug() << "ERROR, check port name";
      }

      while (arduino.isConnected()){
        //Check if data has been read or not
        int bytes_read = arduino.readSerialPort(incomingData, MAX_DATA_LENGTH);
        //prints out data
            if (bytes_read) {
                dataString = static_cast<QString>(incomingData).left(bytes_read);
                qDebug() << dataString;
                parseTransmission(dataString);
            }
        //wait a bit
        Sleep(10);
      }
}

//void ArduinoInterface::clearAlarms() {
//    for (int i = 1; i < DEVICECOUNT; i++) {
//        fieldDevice[i].clearAlarms();
//    }
//}

void ArduinoInterface::parseTransmission(QString datastring) {
    if (datastring.left(1) == ">" && datastring.mid(4,1) == ";") {
        QString txType = datastring.mid(1,3); //Read three-letter tx code and semicolon
        datastring.remove(0,5);
        if (txType == "DAT") {
            parseValuesToSatellite(datastring);
        }
        else if (txType == "STS") {
            int deviceID = datastring.left(1).toInt();
            datastring.remove(0,2);
            bool status = (datastring.left(1) == "1") ? true : false;
            qDebug() << "Setting device status to " << status << "\n";
            fieldDevice[deviceID].deviceStatus.setValue(status);
        }
        else if (txType == "ALM") {
            int deviceID = datastring.left(1).toInt();
            QString alarmType = datastring.left(2);
            datastring.remove(0,3);
            // IMPLEMENT ALARM TEXT PARSING
            // IMPLEMENT TIME TRACKING FOR ALARMS
            // IMPLEMENT ENUM FOR ALARM TYPES, MAYBE?
            fieldDevice[deviceID].deviceStatus.throwAlarm(alarmType);
        }

        while (!datastring.isEmpty() && datastring.left(1) != ">") {
            datastring.remove(0,1);
        }

        if (!datastring.isEmpty()) {
            parseTransmission(datastring); // Recursive parse in case of backed-up transmissions.
        }
    }


}

void ArduinoInterface::parseValuesToSatellite(QString datastring) {
    bool validDatastring = true;
    QString secondsElapseStr = "";
    int deviceID = 0;
    unsigned long int secondsElapsed = 0;
    int temperature_0 = 0;
    int humidity_0 = 0;
    int temperature_1 = 0;
    int humidity_1 = 0;

    // Parse deviceID
    if (datastring.length() != 0) {
        deviceID = datastring.left(1).toInt();
        datastring.remove(0,1);
    }

    if (datastring.left(1) == ";") {
        datastring.remove(0,1);
    }
    else {
        validDatastring = false;
    }

    // Parse numeric secondsElapsed
    while (datastring.length() != 0 && !datastring.startsWith(";") /*change to ISNUMERIC*/) {
        secondsElapseStr.append(datastring.left(1));
        datastring.remove(0,1);
    }

    secondsElapsed = static_cast<unsigned long int>(secondsElapseStr.toInt());

    if (datastring.left(1) == ";") {
        datastring.remove(0,1);
    }
    else {
        validDatastring = false;
    }

    // Parse temperature_0
    if (datastring.length() != 0) {
        temperature_0 = datastring.left(3).toInt(); //Should always be 3 digits in practice
        datastring.remove(0,3);
    }

    if (datastring.left(1) == ";") {
        datastring.remove(0,1);
    }
    else {
        validDatastring = false;
    }

    // Parse humidity_0
    if (datastring.length() != 0) {
        humidity_0 = datastring.left(3).toInt(); //Should always be 3 digits in practice
        datastring.remove(0,3);
    }

    if (datastring.left(1) == ";") {
        datastring.remove(0,1);
    }
    else {
        validDatastring = false;
    }

    if (datastring.length() != 0 && datastring.mid(3, 1) == ";" && datastring.mid(7, 1) == ";") {
        temperature_1 = datastring.left(3).toInt(); //Should always be 3 digits in practice
        datastring.remove(0,4); //todo do a cleaner check later.  perhaps transmissions should have a termination character.

        humidity_1 = datastring.left(3).toInt(); //Should always be 3 digits in practice
        datastring.remove(0,4);
    }

    // Push new values to satellite
    if (temperature_1 && humidity_1) {
        fieldDevice[deviceID].updateValues(secondsElapsed, temperature_0, humidity_0, temperature_1, humidity_1);
    }
    else {
        fieldDevice[deviceID].updateValues(secondsElapsed, temperature_0, humidity_0);
    }
}
