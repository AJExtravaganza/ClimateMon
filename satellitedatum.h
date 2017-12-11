#ifndef SATELLITEDATUM_H
#define SATELLITEDATUM_H

#include <QObject>
#include "processvalue.h"

////DON'T BE SURPRISED IF THIS NEEDS THE BIG 3 CONSTRUCTORS AT SOME STAGE.  MAY BE TRUE FOR ALL QObjects

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
