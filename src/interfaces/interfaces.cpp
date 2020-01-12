#include "main.h"
#include "interfaces.h"
#include "nixietube/nixietube.h"
#include "battery/battery.h"
#include "basic/basic.h"
#include "ntp/ntpInterface.h"

NixieTube1 i1 = NixieTube1();
NixieTube2 i2 = NixieTube2();
NixieTube3 i3 = NixieTube3();
BatteryInterface i4 = BatteryInterface();
BasicInterface i5 = BasicInterface();
NtpInterface i6 = NtpInterface();

Interfaces::Interfaces()
{
    totalInterfaces = 0;
}

void Interfaces::begin()
{
    addInterface(&i1);
    addInterface(&i2);
    addInterface(&i3);
    addInterface(&i4);
    addInterface(&i5);
    addInterface(&i6);
    Serial.println("Interfaces: loaded!");
}

void Interfaces::addInterface(WatchInterface *interface)
{
    interfaces[totalInterfaces] = interface;
    totalInterfaces++;
}

void Interfaces::setupInterface()
{
    interfaces[config.screen_watchInterface]->setup();
}

void Interfaces::finishInterface()
{
    interfaces[config.screen_watchInterface]->finish();
}

void Interfaces::loopInterface()
{
    interfaces[config.screen_watchInterface]->loop();
}

void Interfaces::pressA()
{
    interfaces[config.screen_watchInterface]->pressA();
}

void Interfaces::pressB()
{
    interfaces[config.screen_watchInterface]->pressB();
}