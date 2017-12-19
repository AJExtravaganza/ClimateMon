#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    baseDeviceInterface.start();

    QObject::connect(&baseDeviceInterface.fieldDevice[1].climateData.temperature, SIGNAL(valueChanged(QString)), ui->sat1Temperature, SLOT(display(QString)));
    QObject::connect(&baseDeviceInterface.fieldDevice[1].climateData.humidity, SIGNAL(valueChanged(QString)), ui->sat1Humidity, SLOT(display(QString)));
    QObject::connect(&baseDeviceInterface.fieldDevice[2].climateData.temperature, SIGNAL(valueChanged(QString)), ui->sat2Temperature, SLOT(display(QString)));
    QObject::connect(&baseDeviceInterface.fieldDevice[2].climateData.humidity, SIGNAL(valueChanged(QString)), ui->sat2Humidity, SLOT(display(QString)));
    QObject::connect(&baseDeviceInterface.fieldDevice[3].climateData.temperature, SIGNAL(valueChanged(QString)), ui->sat1Temperature, SLOT(display(QString)));
    QObject::connect(&baseDeviceInterface.fieldDevice[3].climateData.humidity, SIGNAL(valueChanged(QString)), ui->sat3Humidity, SLOT(display(QString)));

    QObject::connect(&baseDeviceInterface.fieldDevice[1].deviceStatus, SIGNAL(valueChanged(QString)), ui->SatStatus_1, SLOT(setText(QString)));
    QObject::connect(&baseDeviceInterface.fieldDevice[2].deviceStatus, SIGNAL(valueChanged(QString)), ui->SatStatus_2, SLOT(setText(QString)));
    QObject::connect(&baseDeviceInterface.fieldDevice[3].deviceStatus, SIGNAL(valueChanged(QString)), ui->SatStatus_3, SLOT(setText(QString)));
   }

Widget::~Widget()
{
    baseDeviceInterface.quit(); //It is necessary to quit the background thread before terminating the application.
    if(!baseDeviceInterface.wait(3000)) //Wait until it actually has terminated (max. 3 sec)
    {
        baseDeviceInterface.terminate(); //Thread didn't exit in time, probably deadlocked, terminate it!
        baseDeviceInterface.wait(); //We have to wait again here!
    }
    delete ui;
}
