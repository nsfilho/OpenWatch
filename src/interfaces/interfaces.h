#ifndef __INTERFACES_H_
#define __INTERFACES_H_
#include "watch_interface.h"

#define MAX_INTERFACES 10

class Interfaces
{
private:
    WatchInterface *interfaces[10];

public:
    byte totalInterfaces;
    Interfaces();
    void begin();
    void addInterface(WatchInterface *interface);
    bool setupInterface();
    void finishInterface();
    bool loopInterface();
    void pressA();
    void pressB();
};

#endif