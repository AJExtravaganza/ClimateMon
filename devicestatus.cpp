#include "devicestatus.h"
#include <QDebug>
#include <QDir>

DeviceStatus::DeviceStatus(QObject *parent) : QObject(parent), value(1)//, touched(false)
{

}

bool DeviceStatus::getValue() {
    return value;
}

bool DeviceStatus::getAlarm() {
    return inAlarm;
}

void DeviceStatus::setValue(bool value) {

    DeviceStatus::value = value;
    if (!value) {
        throwAlarm("DN");
    }

    // Updates dont occur often enough to pose a performance concern, and updating each time is cleaner than messy conditionals
    QString statusText = value ? "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt; font-weight:600; color:#228B22;\">OK</span></p></body></html>" : "<html><head/><body><p align=\"center\"><span style=\" font-size:10pt; font-weight:600; color:#aa0000;\">COMMS FAIL</span></p></body></html>";
    emit valueChanged(statusText);
}

void DeviceStatus::setAlarm(bool alarmStatus) {
    inAlarm = alarmStatus;
}

void DeviceStatus::throwAlarm(QString alarmType) {
    //loads alarm indicator image
    QDir alarmLEDFile("alarmLED.png");
    QPicture alarmLEDPicture;
    alarmLEDPicture.load(alarmLEDFile.absolutePath(), "png");

    if (alarmType == "DN") {
        commsAlarm = true;
        emit commsAlarmActivated(alarmLEDPicture);
    }
    else if (alarmType == "LT") {
        tempAlarm = true;
        emit tempAlarmActivated(alarmLEDPicture);
    }
    else if (alarmType == "HT") {
        tempAlarm = true;
        emit tempAlarmActivated(alarmLEDPicture);
    }
    else if (alarmType == "LH") {
        humAlarm = true;
        emit humAlarmActivated(alarmLEDPicture);
    }
    else if (alarmType == "HH") {
        humAlarm = true;
        emit humAlarmActivated(alarmLEDPicture);
    }

    inAlarm = true;
    emit alarmActivated();
}

void DeviceStatus::clearAlarms() {
    commsAlarm = false;
    tempAlarm = false;
    humAlarm = false;
    inAlarm = false;
}

//// SHOULD USE PREPROCESSORS TO ALLOW EASY EDITING OF TEXT LABEL
