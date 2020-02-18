#ifndef __BATTERY_INTERFACE_H_
#define __BATTERY_INTERFACE_H_

#include "watch_interface.h"

class BatteryInterface : public WatchInterface
{
public:
    bool setup();
    bool loop();
    void finish();
};

#endif