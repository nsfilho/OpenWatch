#include "main.h"
#include "interfaces.h"
#include "nixietube/nixietube.h"
#include "battery/battery.h"
#include "basic/basic.h"
#include "ntp/ntpInterface.h"
#include "weather/weather.h"

NixieTube1 i1 = NixieTube1();
// NixieTube2 i2 = NixieTube2();
// NixieTube3 i3 = NixieTube3();
BatteryInterface i4 = BatteryInterface();
BasicInterface i5 = BasicInterface();
NtpInterface i6 = NtpInterface();
WeatherInterface i7 = WeatherInterface();

Interfaces::Interfaces()
{
    totalInterfaces = 0;
}

void Interfaces::begin()
{
    addInterface(&i1);
    // addInterface(&i2);
    // addInterface(&i3);
    addInterface(&i4);
    addInterface(&i5);
    addInterface(&i6);
    addInterface(&i7);
}

void Interfaces::addInterface(WatchInterface *interface)
{
    interfaces[totalInterfaces] = interface;
    totalInterfaces++;
}

bool Interfaces::setupInterface()
{
    return interfaces[config.screen_watchInterface]->setup();
}

void Interfaces::finishInterface()
{
    interfaces[config.screen_watchInterface]->finish();
}

bool Interfaces::loopInterface()
{
    return interfaces[config.screen_watchInterface]->loopStatus();
}

void Interfaces::pressA()
{
    interfaces[config.screen_watchInterface]->pressA();
}

void Interfaces::pressB()
{
    interfaces[config.screen_watchInterface]->pressB();
}

WatchInterface *Interfaces::getCurrent()
{
    return interfaces[config.screen_watchInterface];
}