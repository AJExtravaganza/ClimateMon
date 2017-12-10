#ifndef SATELLITEDATUM_H
#define SATELLITEDATUM_H

#include <QObject>
#include "processvalue.h"

class SatelliteDatum : public QObject //Figure out later whether this really needs to be a QObject
{
    Q_OBJECT

public:
    explicit SatelliteDatum(QObject *parent = nullptr);
    unsigned long int lastUpdated; //Change to a proper system-time-based timestamp later
    ProcessValue temperature;
    ProcessValue humidity;

signals:

public slots:
};

#endif // SATELLITEDATUM_H
