#ifndef __WEATHER_H_
#define __WEATHER_H_
#include "watch_interface.h"

#define STATUS_INFO_TEMP 0
#define STATUS_INFO_PLUVIOMETRIC 1
#define STATUS_INFO_READINFO 2
#define STATUS_INFO_TIMEOUT 3000

class WeatherInterface : public WatchInterface
{

public:
    WeatherInterface();
    bool setup();
    bool loop();
    bool needUpdate();
    void updateInfo();
    void pressB();
    void startUpdate();
};

#endif