#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "arduinointerface.h"

namespace Ui {
class Widget;
}

class CliMonWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CliMonWindow(QWidget *parent = 0);
    ~CliMonWindow();
    ArduinoInterface baseDeviceInterface; //Maybe should be private

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
