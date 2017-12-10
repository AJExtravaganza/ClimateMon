#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "arduinointerface.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    ArduinoInterface baseLink; //Maybe should be private

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
