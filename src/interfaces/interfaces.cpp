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

void Interfaces::Interfaces()
{
    addInterface(new NixieTube1());
    addInterface(new BatteryInterface());
    addInterface(new BasicInterface());
    addInterface(new WeatherInterface());
    addInterface(new NtpInterface());
    addInterface(new WebInterface());
}

void Interfaces::addInterface(WatchInterface *interface)
{
    interfaces.push_back(interface);
}


WatchInterface *Interfaces::getCurrent()
{
    return interfaces[config.screen_watchInterface];
}

WatchInterface *Interfaces::nextInterface()
{
    getCurrent()->finish();
    if (config.screen_watchInterface+1 > interfaces.size())
        config.screen_watchInterface = 0;
    else
        config.screen_watchInterface++;
    return interfaces[config.screen_watchInterface];
}

void Interfaces::loop()
{
    getCurrent()->update();
    if (millis() - lastUpdate > config.screen_refreshTime) {
        if (getCurrent()->useRTC)
            getRTC_info();

        // test if screen was update
        if (getCurrent()->loop()) {
            tftSprite.pushSprite(0, 0);
        }
    }
}

