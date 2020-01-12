#ifndef __NIXIETUBE_H_
#define __NIXIETUBE_H_
#include "watch_interface.h"

class NixieTube1 : public WatchInterface
{
public:
    void setup();
    void loop();
};

class NixieTube2 : public WatchInterface
{
public:
    void setup();
    void loop();
};

class NixieTube3 : public WatchInterface
{
public:
    void setup();
    void loop();
};

void nixietube_setup();

#endif