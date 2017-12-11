#include "arduinointerface.h"
#include <qdebug.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SerialPort.h"

using std::cout;
using std::endl;

ArduinoInterface::ArduinoInterface(): liveDevices({0,0,0,0,0,0})
{

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
                update(dataString);
            }
        //wait a bit
        Sleep(10);
      }
}

void ArduinoInterface::update(QString datastring) {
    bool validDatastring = true;
    QString timestampStr = "";
    unsigned long int timestamp = 0;
    int deviceID = 0;
    int temperature = 0;
    int humidity = 0;

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

    while (datastring.length() != 0 && !datastring.startsWith(";") /*change to ISNUMERIC*/) {
        timestampStr.append(datastring.left(1));
        datastring.remove(0,1);
    }

    timestamp = static_cast<unsigned long int>(timestampStr.toInt());

    if (datastring.left(1) == ";") {
        datastring.remove(0,1);
    }
    else {
        validDatastring = false;
    }

    if (datastring.length() != 0) {
        temperature = datastring.left(3).toInt(); //Should always be 3 digits in practice
        datastring.remove(0,3);
    }

    if (datastring.left(1) == ";") {
        datastring.remove(0,1);
    }
    else {
        validDatastring = false;
    }

    if (datastring.length() != 0) {
        humidity = datastring.left(3).toInt(); //Should always be 3 digits in practice
        datastring.remove(0,3);
    }

    if (datastring.left(1) == ";") {
        datastring.remove(0,1);
    }
    else {
        validDatastring = false;
    }

    if (validDatastring) {
        climateData[deviceID].temperature.setValue(temperature);
        climateData[deviceID].humidity.setValue(humidity);
        climateData[deviceID].lastUpdated = timestamp;

        //Write to element of array of QFile pointers here.
    }


}
