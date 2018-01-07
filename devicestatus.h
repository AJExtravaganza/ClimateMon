#ifndef DEVICESTATUS_H
#define DEVICESTATUS_H

#include <QObject>
#include <QPicture>

class DeviceStatus : public QObject
{
    Q_OBJECT
private:
    bool value;
    bool inAlarm;
    bool commsAlarm;
    bool tempAlarm; //split into high and low later
    bool humAlarm;

public:
    explicit DeviceStatus(QObject *parent = nullptr);
    bool getValue();
    bool getAlarm();
    void setValue(bool value);
    void setAlarm(bool alarmStatus);
    void throwAlarm(QString alarmType);
    void clearAlarms();

signals:
    void valueChanged(QString text);
    void alarmActivated();
    void commsAlarmActivated(QPicture indicatorImage);
    void tempAlarmActivated(QPicture indicatorImage);
    void humAlarmActivated(QPicture indicatorImage);
    //void alarmCleared();

public slots:
};

#endif // DEVICESTATUS_H
