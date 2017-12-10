#include "processvalue.h"

ProcessValue::ProcessValue(QObject *parent) : QObject(parent), value(0)
{

}

int ProcessValue::getValue() {
    return value;
}

void ProcessValue::setValue(int value) {
    if (value != ProcessValue::value) {
        QString valueAsString = QString::number(value).insert(2,'.');
        ProcessValue::value = value;
        emit valueChanged(valueAsString);
    }

}
