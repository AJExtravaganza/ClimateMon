#ifndef DATALOGGER_H
#define DATALOGGER_H

#include <QFile>
#include <QString>
#include "satellitedatum.h"

class Datalogger
{
private:
    QFile* datalog;
    QString generateRecord(SatelliteDatum &datum);
public:
    Datalogger();
    Datalogger(QFile* datalog);
    void log(SatelliteDatum &datum);
};

#endif // DATALOGGER_H
