#ifndef DEVICESTATUS_H
#define DEVICESTATUS_H

#include <QObject>

class DeviceStatus : public QObject
{
    Q_OBJECT
private:
    bool value;
    bool touched; // Has a valid status ever been received, or are we waiting for the first transmission?

public:
    explicit DeviceStatus(QObject *parent = nullptr);
    bool getValue();
    void setValue(bool value);

signals:
    void valueChanged(QString text);

public slots:
};

#endif // DEVICESTATUS_H
