#include "devicestatus.h"
#include <QDebug>

DeviceStatus::DeviceStatus(QObject *parent) : QObject(parent), value(1)//, touched(false)
{

}

void DeviceStatus::setValue(bool value) {

    DeviceStatus::value = value;

    // Updates dont occur often enough to pose a performance concern, and updating each time is cleaner than messy conditionals
    QString statusText = value ? "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt; font-weight:600; color:#228B22;\">OK</span></p></body></html>" : "<html><head/><body><p align=\"center\"><span style=\" font-size:10pt; font-weight:600; color:#aa0000;\">COMMS FAIL</span></p></body></html>";
    emit valueChanged(statusText);

    //touched = true;
}

