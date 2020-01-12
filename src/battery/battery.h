#ifndef __BATTERY_H_
#define __BATTERY_H_

#include "watch_interface.h"

class Battery : public WatchInterface
{
public:
    void setup();
    void loop();
    void finish();
};

#endif