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

ArduinoInterface::ArduinoInterface(): HYSTERESIS(5)
{
    for (int i = 1; i < DEVICECOUNT; i++) {
        deviceStatus[i].setValue(true);
    }
}

void ArduinoInterface::initialiseDatalogger(int deviceID) {
    //Create a date/timestamp to avoid overwriting old logs
    QDate systemDate = QDate::currentDate();
    QTime systemTime = QTime::currentTime();
    QString dateTimeStr = "";

    //Append YYYYMMDD to date/timestamp
    dateTimeStr.append(QString::number(systemDate.year()));
    dateTimeStr.append((systemDate.month() < 10) ? "0" : "");
    dateTimeStr.append(QString::number(systemDate.month()));
    dateTimeStr.append((systemDate.day() < 10) ? "0" : "");
    dateTimeStr.append(QString::number(systemDate.day()));
    dateTimeStr.append(";");

    //Append hhmmss to date/timestamp
    dateTimeStr.append((systemTime.hour() < 10) ? "0" : "");
    dateTimeStr.append(QString::number(systemTime.hour()));
    dateTimeStr.append((systemTime.minute() < 10) ? "0" : "");
    dateTimeStr.append(QString::number(systemTime.minute()));
    dateTimeStr.append((systemTime.second() < 10) ? "0" : "");
    dateTimeStr.append(QString::number(systemTime.second()));
    dateTimeStr.append(";");

    //Open a datalogging file
   datalogs[deviceID].setFileName((dateTimeStr + "_satellite_" + QString::number(deviceID) + "_datalog.txt"));
   if (!datalogs[deviceID].open(QIODevice::WriteOnly | QIODevice::Append | QFile::Text)) {
       //Do some error stuff
       qDebug() << "Error opening file for writing.\n";
       /*std::cerr << "Cannot open file for writing: "
                 << qPrintable(file.errorString()) << std::endl;
       */
   }

   //Set up an associated Datalogger
   logger[deviceID].setDatalog(&datalogs[deviceID]);

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
                updateValues(dataString);
            }
        //wait a bit
        Sleep(10);
      }
}

void ArduinoInterface::parse(QString datastring) {
    QString txType = datastring.left(4); //Read three-letter tx code and semicolon
    datastring.remove(0,4);
    if (txType == "DAT;") {
        updateValues(datastring);
    }
    else if (txType == "STS;") {
        //QUICK AND DIRTY.  FIX WHEN NOT TIRED.
        int deviceID = datastring.left(1).toInt();
        datastring.remove(0,2);
        bool status = (datastring.left(1) == "1") ? true : false;
        deviceStatus[deviceID].setValue(status);
        qDebug() << "changed the status\n";
    }
}

void ArduinoInterface::updateValues(QString datastring) {
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

        //Check if file needs to be created
        if (!logger[deviceID].isInitialised()) {
            initialiseDatalogger(deviceID);
        }

        if (abs(temperature - climateData[deviceID].temperature.getValue()) > HYSTERESIS || abs(humidity - climateData[deviceID].humidity.getValue()) > HYSTERESIS) {
            //Update recorded values
            climateData[deviceID].temperature.setValue(temperature);
            climateData[deviceID].humidity.setValue(humidity);
            climateData[deviceID].lastUpdated = timestamp;

            //Write the new record to the associated .txt
            logger[deviceID].log(climateData[deviceID]);
        }
    }


}
