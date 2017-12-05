#ifndef SERIALLINK_H
#define SERIALLINK_H

#include <QThread>

class SerialLink : public QThread
{
public:
    SerialLink();
    void run();
};

#endif // SERIALLINK_H
