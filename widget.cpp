#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QPicture>

CliMonWindow::CliMonWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    baseDeviceInterface.start();

    //Temp/hum readout updates
    QObject::connect(&baseDeviceInterface.fieldDevice[1].climateData.temperature[0], SIGNAL(valueChanged(QString)), ui->sat1Temperature_0, SLOT(display(QString)));
    QObject::connect(&baseDeviceInterface.fieldDevice[1].climateData.humidity[0], SIGNAL(valueChanged(QString)), ui->sat1Humidity_0, SLOT(display(QString)));
    QObject::connect(&baseDeviceInterface.fieldDevice[1].climateData.temperature[1], SIGNAL(valueChanged(QString)), ui->sat1Temperature_1, SLOT(display(QString)));
    QObject::connect(&baseDeviceInterface.fieldDevice[1].climateData.humidity[1], SIGNAL(valueChanged(QString)), ui->sat1Humidity_1, SLOT(display(QString)));

    QObject::connect(&baseDeviceInterface.fieldDevice[2].climateData.temperature[0], SIGNAL(valueChanged(QString)), ui->sat2Temperature, SLOT(display(QString)));
    QObject::connect(&baseDeviceInterface.fieldDevice[2].climateData.humidity[0], SIGNAL(valueChanged(QString)), ui->sat2Humidity, SLOT(display(QString)));
    QObject::connect(&baseDeviceInterface.fieldDevice[3].climateData.temperature[0], SIGNAL(valueChanged(QString)), ui->sat3Temperature, SLOT(display(QString)));
    QObject::connect(&baseDeviceInterface.fieldDevice[3].climateData.humidity[0], SIGNAL(valueChanged(QString)), ui->sat3Humidity, SLOT(display(QString)));

    //Comms status label updates
    QObject::connect(&baseDeviceInterface.fieldDevice[1].deviceStatus, SIGNAL(valueChanged(QString)), ui->SatStatus_1, SLOT(setText(QString)));
    QObject::connect(&baseDeviceInterface.fieldDevice[2].deviceStatus, SIGNAL(valueChanged(QString)), ui->SatStatus_2, SLOT(setText(QString)));
    QObject::connect(&baseDeviceInterface.fieldDevice[3].deviceStatus, SIGNAL(valueChanged(QString)), ui->SatStatus_3, SLOT(setText(QString)));

    //Alarm tone triggers
    QObject::connect(&baseDeviceInterface.fieldDevice[1].deviceStatus, SIGNAL(alarmActivated()), &baseDeviceInterface.alarmTone, SLOT(play()));
    //implement others later

    //Alarm visual notification triggers

    //QObject::connect(&baseDeviceInterface.fieldDevice[1].deviceStatus, SIGNAL(commsAlarmActivated(QPicture)), ui->AlarmIndicator_1, SLOT(setPicture(QPicture)));
    //implement others later

    //Alarm mute pushbutton
    //QObject::connect(ui->alarmMutePB, SIGNAL(clicked(bool)), &baseDeviceInterface.alarmTone, SLOT(stop()));
   }

CliMonWindow::~CliMonWindow()
{
    baseDeviceInterface.quit(); //It is necessary to quit the background thread before terminating the application.
    if(!baseDeviceInterface.wait(3000)) //Wait until it actually has terminated (max. 3 sec)
    {
        baseDeviceInterface.terminate(); //Thread didn't exit in time, probably deadlocked, terminate it!
        baseDeviceInterface.wait(); //We have to wait again here!
    }
    delete ui;
}
