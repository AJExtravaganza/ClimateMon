#ifndef SATELLITEDATUM_H
#define SATELLITEDATUM_H

#include <QObject>
#include "processvalue.h"

class SatelliteDatum : public QObject //Figure out later whether this really needs to be a QObject
{
    Q_OBJECT

public:
    explicit SatelliteDatum(QObject *parent = nullptr);
    unsigned long int lastUpdated; //seconds elapsed since base station powered on.  Useful for graphing vs time.
    ProcessValue temperature[2];
    ProcessValue humidity[2];

signals:

public slots:
};

#endif // SATELLITEDATUM_H
