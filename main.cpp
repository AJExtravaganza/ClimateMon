#include <QApplication>
#include <QFile>
#include <QDate>
#include <QTime>
#include "arduinointerface.h"
#include "widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();


    return a.exec();
}
