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
    deviceStatus.clearAlarms();
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

void Satellite::updateValues(unsigned long int secondsElapsed, int temperature, int humidity) {

    //Check if file needs to be created
    if (!logger.isInitialised()) {
        initialiseDatalogger();
    }

    //// TODO: ADD CHECK FOR PRECIPITOUS DROP AND WRITE RECORD IF EXISTS FOR QUALITY GRAPHING

    if (abs(temperature - climateData.temperature[0].getValue()) > TEMPHYSTERESIS ||
        abs(humidity - climateData.humidity[0].getValue()) > HUMHYSTERESIS) {
        //Update recorded values
        climateData.temperature[0].setValue(temperature);
        climateData.humidity[0].setValue(humidity);
        climateData.lastUpdated = secondsElapsed;

        //Write the new record to the associated .txt
        logger.log(climateData);
    }
}

void Satellite::updateValues(unsigned long int secondsElapsed, int temperature_0, int humidity_0, int temperature_1, int humidity_1) {

    //Check if file needs to be created
    if (!logger.isInitialised()) {
        initialiseDatalogger();
    }

    //// TODO: ADD CHECK FOR PRECIPITOUS DROP AND WRITE RECORD IF EXISTS FOR QUALITY GRAPHING

    if (abs(temperature_0 - climateData.temperature[0].getValue()) > TEMPHYSTERESIS ||
        abs(humidity_0 - climateData.humidity[0].getValue()) > HUMHYSTERESIS ||
        abs(temperature_1 - climateData.temperature[1].getValue()) > TEMPHYSTERESIS ||
        abs(humidity_1 - climateData.humidity[1].getValue()) > HUMHYSTERESIS) {
        //Update recorded values

        climateData.temperature[0].setValue(temperature_0);
        climateData.humidity[0].setValue(humidity_0);
        climateData.temperature[1].setValue(temperature_1);
        climateData.humidity[1].setValue(humidity_1);
        climateData.lastUpdated = secondsElapsed;

        //Write the new record to the associated .txt
        logger.log(climateData);
    }
}
