#ifndef __WEATHER_H_
#define __WEATHER_H_
#include <M5StickC.h>
#include "watch_interface.h"

class WeatherInterface : public WatchInterface
{
public:
    bool setup();
    bool loop();
    bool needUpdate();
    void finish();
    void updateInfo();
    void pressB();
    void startUpdate();
};

#endif