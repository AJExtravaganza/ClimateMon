#include "datalogger.h"
#include <QDate>
#include <QTime>
#include <QDebug>

Datalogger::Datalogger() : datalog(nullptr) {

}

QString Datalogger::generateRecord(SatelliteDatum &datum) {
    QString record = "";
    QDate systemDate = QDate::currentDate();
    QTime systemTime = QTime::currentTime();

    //Date field YYYYMMDD
    record.append(QString::number(systemDate.year()));
    record.append((systemDate.month() < 10) ? "0" : "");
    record.append(QString::number(systemDate.month()));
    record.append((systemDate.day() < 10) ? "0" : "");
    record.append(QString::number(systemDate.day()));
    record.append(";");

    //Time field hhmmss
    record.append((systemTime.hour() < 10) ? "0" : "");
    record.append(QString::number(systemTime.hour()));
    record.append((systemTime.minute() < 10) ? "0" : "");
    record.append(QString::number(systemTime.minute()));
    record.append((systemTime.second() < 10) ? "0" : "");
    record.append(QString::number(systemTime.second()));
    record.append(";");

    //SECONDS ELAPSED GOES HERE
    record.append(QString::number(datum.lastUpdated));
    record.append(";");

    //Sensor 0 Temperature °C
    record.append(datum.temperature[0].getValueAsStr());
    record.append(";");

    //Sensor 0 Relative humidity %RH
    record.append(datum.humidity[0].getValueAsStr());
    record.append(";");

    //If there is a second sensor, append its values too.
    //Sensor is present if values are non-default (ie != -1)
    if (datum.temperature[1].getValue() != -1 && datum.humidity[1].getValue() != -1) {

        //Sensor 1 Temperature °C
        record.append(datum.temperature[1].getValueAsStr());
        record.append(";");

        //Sensor 1 Relative humidity %RH
        record.append(datum.humidity[1].getValueAsStr());
        record.append(";");
    }

    //EoL
    record.append("\n");

    return record;

}

bool Datalogger::isInitialised() {
    return datalog;
}

void Datalogger::setDatalog(QFile* datalog) {
    Datalogger::datalog = datalog;
    logStream.setDevice(datalog);
}

void Datalogger::log(SatelliteDatum &datum) {

    QString record = generateRecord(datum);
    qDebug() << "Writing " << record << " to file.\n";
    logStream << record;
}
