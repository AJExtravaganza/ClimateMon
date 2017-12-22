#include "satellite.h"

#include "Satellite.h"
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

Satellite::Satellite(): TEMPHYSTERESIS(USERTEMPHYSTERESIS), HUMHYSTERESIS(USERHUMHYSTERESIS), deviceID(-1)
{

}

Satellite::Satellite(int deviceID): TEMPHYSTERESIS(USERTEMPHYSTERESIS), HUMHYSTERESIS(USERHUMHYSTERESIS), deviceID(deviceID)
{

}

void Satellite::setDeviceID(int deviceID) {
    Satellite::deviceID = deviceID;
}

void Satellite::clearAlarms() {
    deviceStatus.clearAlarm();
}


void Satellite::initialiseDatalogger() {
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
   datalog.setFileName((dateTimeStr + "_satellite_" + QString::number(deviceID) + "_datalog.txt"));
   if (!datalog.open(QIODevice::WriteOnly | QIODevice::Append | QFile::Text)) {
       //Do some error stuff
       qDebug() << "Error opening file for writing.\n";
       /*std::cerr << "Cannot open file for writing: "
                 << qPrintable(file.errorString()) << std::endl;
       */
   }

   //Set up an associated Datalogger
   logger.setDatalog(&datalog);

}

//void Satellite::run() {

//    /*Portname must contain these backslashes, and remember to
//    replace the following com port*/
//    QString port_name = "\\\\.\\COM4";

//    //String for incoming data
//    char incomingData[MAX_DATA_LENGTH];
//    QString dataString = "";

//    SerialPort arduino(port_name);
//      if (arduino.isConnected()) {
//          qDebug() << "Connection Established" << endl;
//      }
//      else {
//          qDebug() << "ERROR, check port name";
//      }

//      while (arduino.isConnected()){
//        //Check if data has been read or not
//        int bytes_read = arduino.readSerialPort(incomingData, MAX_DATA_LENGTH);
//        //prints out data
//            if (bytes_read) {
//                dataString = static_cast<QString>(incomingData).left(bytes_read);
//                qDebug() << dataString;
//                parse(dataString);
//            }
//        //wait a bit
//        Sleep(10);
//      }
//}

//void Satellite::parse(QString datastring) {
//    if (datastring.left(1) == ">" && datastring.mid(4,1) == ";") {
//        QString txType = datastring.mid(1,3); //Read three-letter tx code and semicolon
//        datastring.remove(0,5);
//        if (txType == "DAT") {
//            updateValues(datastring);
//        }
//        else if (txType == "STS") {
//            int deviceID = datastring.left(1).toInt();
//            datastring.remove(0,2);
//            bool status = (datastring.left(1) == "1") ? true : false;
//            qDebug() << "Setting device status to " << status << "\n";
//            deviceStatus[deviceID].setValue(status);
//        }

//        while (!datastring.isEmpty() && datastring.left(1) != ">") {
//            datastring.remove(0,1);
//        }

//        if (!datastring.isEmpty()) {
//            parse(datastring); // Recursive parse in case of backed-up transmissions.
//        }
//    }
//}

void Satellite::updateValues(unsigned long int secondsElapsed, int temperature, int humidity) {

//    QString timestampStr = "";

//    // Parse deviceID
//    if (datastring.length() != 0) {
//        deviceID = datastring.left(1).toInt();
//        datastring.remove(0,1);
//    }

//    if (datastring.left(1) == ";") {
//        datastring.remove(0,1);
//    }
//    else {
//        validDatastring = false;
//    }

//    // Parse numeric secondsElapsed
//    while (datastring.length() != 0 && !datastring.startsWith(";") /*change to ISNUMERIC*/) {
//        timestampStr.append(datastring.left(1));
//        datastring.remove(0,1);
//    }

//    secondsElapsed = static_cast<unsigned long int>(timestampStr.toInt());

//    if (datastring.left(1) == ";") {
//        datastring.remove(0,1);
//    }
//    else {
//        validDatastring = false;
//    }

//    // Parse temperature
//    if (datastring.length() != 0) {
//        temperature = datastring.left(3).toInt(); //Should always be 3 digits in practice
//        datastring.remove(0,3);
//    }

//    if (datastring.left(1) == ";") {
//        datastring.remove(0,1);
//    }
//    else {
//        validDatastring = false;
//    }

//    // Parse humidity
//    if (datastring.length() != 0) {
//        humidity = datastring.left(3).toInt(); //Should always be 3 digits in practice
//        datastring.remove(0,3);
//    }

//    if (datastring.left(1) == ";") {
//        datastring.remove(0,1);
//    }
//    else {
//        validDatastring = false;
//    }

//    // Perform update if datastring is valid
//    if (validDatastring) {

        //Check if file needs to be created
        if (!logger.isInitialised()) {
            initialiseDatalogger();
        }

        //// TODO: ADD CHECK FOR PRECIPITOUS DROP AND WRITE RECORD IF EXISTS FOR QUALITY GRAPHING

        if (abs(temperature - climateData.temperature.getValue()) > TEMPHYSTERESIS || abs(humidity - climateData.humidity.getValue()) > HUMHYSTERESIS) {
            //Update recorded values
            climateData.temperature.setValue(temperature);
            climateData.humidity.setValue(humidity);
            climateData.lastUpdated = secondsElapsed;

            //Write the new record to the associated .txt
            logger.log(climateData);
        }
//    }
}
