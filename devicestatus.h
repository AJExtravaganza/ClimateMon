#ifndef DEVICESTATUS_H
#define DEVICESTATUS_H

#include <QObject>

class DeviceStatus : public QObject
{
    Q_OBJECT
private:
    //int deviceID;
    bool value;

public:
    explicit DeviceStatus(QObject *parent = nullptr);
    bool getValue();
    void setValue(bool value);

signals:
    void valueChanged(QString text);

public slots:
};

#endif // DEVICESTATUS_H
