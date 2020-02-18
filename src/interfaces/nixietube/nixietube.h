#ifndef __NIXIETUBE_H_
#define __NIXIETUBE_H_
#include "watch_interface.h"

class NixieTube1 : public WatchInterface
{
public:
    bool setup();
    bool loop();
};

class NixieTube2 : public WatchInterface
{
public:
    bool setup();
    bool loop();
};

class NixieTube3 : public WatchInterface
{
public:
    bool setup();
    bool loop();
};

bool nixietube_setup();

#endif