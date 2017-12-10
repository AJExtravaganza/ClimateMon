#ifndef PROCESSVALUE_H
#define PROCESSVALUE_H

#include <QObject>

class ProcessValue : public QObject
{
    Q_OBJECT
private:
    int value;

public:
    explicit ProcessValue(QObject *parent = nullptr);
    int getValue();

signals:
    void valueChanged(int newValue);
    void valueChanged(QString newValueAsQString);

public slots:
    void setValue(int value);
};

#endif // PROCESSVALUE_H
