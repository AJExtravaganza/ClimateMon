#include <QApplication>
#include <QFile>
#include <QDate>
#include <QTime>
#include "arduinointerface.h"
#include "widget.h"
#include <QSound>
#include <QDir>
#include <QDebug>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    CliMonWindow w;
    w.show();

    //w.baseDeviceInterface.alarmTone.play();

//    QDir alarmSoundFile("alarmshort.wav");
//    qDebug() << alarmSoundFile.exists() << 'n';
//    qDebug() << alarmSoundFile.absolutePath() << 'n';
//    QSound effect(alarmSoundFile.absolutePath());
//    effect.play();

    return a.exec();
}
