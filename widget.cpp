#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    baseLink.start();

    QObject::connect(&baseLink.climateData[1].temperature, SIGNAL(valueChanged(QString)), ui->sat1Temperature, SLOT(display(QString)));
    QObject::connect(&baseLink.climateData[1].humidity, SIGNAL(valueChanged(QString)), ui->sat1Humidity, SLOT(display(QString)));
    QObject::connect(&baseLink.climateData[2].temperature, SIGNAL(valueChanged(QString)), ui->sat2Temperature, SLOT(display(QString)));
    QObject::connect(&baseLink.climateData[2].humidity, SIGNAL(valueChanged(QString)), ui->sat2Humidity, SLOT(display(QString)));
    QObject::connect(&baseLink.climateData[3].temperature, SIGNAL(valueChanged(QString)), ui->sat1Temperature, SLOT(display(QString)));
    QObject::connect(&baseLink.climateData[3].humidity, SIGNAL(valueChanged(QString)), ui->sat3Humidity, SLOT(display(QString)));
}

Widget::~Widget()
{
    baseLink.quit(); //It is necessary to quit the background thread before terminating the application.
    if(!baseLink.wait(3000)) //Wait until it actually has terminated (max. 3 sec)
    {
        baseLink.terminate(); //Thread didn't exit in time, probably deadlocked, terminate it!
        baseLink.wait(); //We have to wait again here!
    }
    delete ui;
}
