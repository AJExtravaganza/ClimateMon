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

    //Temperature field °C
    record.append(datum.temperature.getValueAsStr());
    record.append(";");

    //Relative humidity %RH
    record.append(datum.humidity.getValueAsStr());
    record.append(";");

    //EoL
    record.append("\n");

    return record;

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
