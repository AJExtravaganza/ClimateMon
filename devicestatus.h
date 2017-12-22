#ifndef DEVICESTATUS_H
#define DEVICESTATUS_H

#include <QObject>

class DeviceStatus : public QObject
{
    Q_OBJECT
private:
    bool value;
    bool inAlarm;
   // bool touched; // Has a valid status ever been received, or are we waiting for the first transmission?

public:
    explicit DeviceStatus(QObject *parent = nullptr);
    bool getValue();
    bool getAlarm();
    void setValue(bool value);
    void setAlarm(bool alarmStatus);
    void throwAlarm();
    void clearAlarm();

signals:
    void valueChanged(QString text);
    void alarmActivated();
    //void alarmCleared();

public slots:
};

#endif // DEVICESTATUS_H
