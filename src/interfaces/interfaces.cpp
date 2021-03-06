/**
 * Openwatch Framework
 * Copyright (C) 2020  Nelio Souza Santos Filho <nsfilho@icloud.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>. 
 *
 */
#include "main.h"
#include "interfaces.h"
#include "nixietube/nixietube.h"
#include "battery/battery.h"
#include "basic/basic.h"
#include "ntp/ntpInterface.h"
#include "weather/weather.h"
#include "web/web.h"

NixieTube1 i1 = NixieTube1();
// NixieTube2 i2 = NixieTube2();
// NixieTube3 i3 = NixieTube3();
BatteryInterface i4 = BatteryInterface();
BasicInterface i5 = BasicInterface();
WeatherInterface i6 = WeatherInterface();
NtpInterface i7 = NtpInterface();
WebInterface i8 = WebInterface();

void Interfaces::begin()
{
    addInterface(&i1);
    // addInterface(&i2);
    // addInterface(&i3);
    addInterface(&i4);
    addInterface(&i5);
    addInterface(&i6);
    addInterface(&i7);
    addInterface(&i8);
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

void Interfaces::pressA(byte count)
{
    interfaces[config.screen_watchInterface]->pressA(count);
}

void Interfaces::pressB(byte count)
{
    interfaces[config.screen_watchInterface]->pressB(count);
}

void Interfaces::update()
{
    interfaces[config.screen_watchInterface]->update();
}

WatchInterface *Interfaces::getCurrent()
{
    return interfaces[config.screen_watchInterface];
}