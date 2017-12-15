#include "devicestatus.h"
#include <QDebug>

DeviceStatus::DeviceStatus(QObject *parent) : QObject(parent), value(1), touched(false)
{
    qDebug() << "status object instantiation (touched = " << touched << ")\n";
}

void DeviceStatus::setValue(bool value) {
    qDebug() << "set the status (touched = " << touched << ")\n";
    if (true || value != DeviceStatus::value || !touched) {
        qDebug() << "status change\n";
        DeviceStatus::value = value;
        touched = true;
        QString statusText = value ? "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt; font-weight:600; color:#228B22;\">OK</span></p></body></html>" : "<html><head/><body><p align=\"center\"><span style=\" font-size:10pt; font-weight:600; color:#aa0000;\">COMMS FAIL</span></p></body></html>";
        qDebug() << "Emitted " << statusText << "\n";
        emit valueChanged(statusText);
    }
}

