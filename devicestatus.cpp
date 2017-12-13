#include "devicestatus.h"

DeviceStatus::DeviceStatus(QObject *parent) : QObject(parent), value(1)
{

}

void DeviceStatus::setValue(bool value) {
    if (value != DeviceStatus::value) {
        DeviceStatus::value = value;
        QString statusText = value ? "<html><head/><body><p align=\"center\"><span style=\" font-size:10pt; font-weight:600; color:#aa0000;\">OK</span></p></body></html>" : "<html><head/><body><p align=\"center\"><span style=\" font-size:10pt; font-weight:600; color:#aa0000;\">NO COMMS</span></p></body></html>";
        emit valueChanged(statusText);
    }
}

