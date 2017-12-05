#include "widget.h"
#include <QApplication>
#include "seriallink.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    SerialLink baseLink;
    baseLink.run();

    return a.exec();
}
