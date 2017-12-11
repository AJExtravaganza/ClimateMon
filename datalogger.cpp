#include "datalogger.h"
#include <QDate>
#include <QTime>

Datalogger::Datalogger() : datalog(nullptr) {

}

Datalogger::Datalogger(QFile* datalog) : datalog(datalog)
{

}

QString Datalogger::generateRecord(SatelliteDatum &datum) {
    QString record = "";
    QDate systemDate = QDate::currentDate();
    QTime systemTime = QTime::currentTime();

    //Date field YYYYMMDD
    record.append(systemDate.year());
    record.append((systemDate.month() < 10) ? "0" : "");
    record.append(systemDate.month());
    record.append((systemDate.day() < 10) ? "0" : "");
    record.append(systemDate.day());
    record.append(";");

    //Time field hhmm
    record.append((systemTime.hour() < 10) ? "0" : "");
    record.append(systemTime.hour());
    record.append((systemTime.minute() < 10) ? "0" : "");
    record.append(systemTime.minute());
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

void Datalogger::log(SatelliteDatum &datum) {

    QString record = generateRecord(datum);
}
