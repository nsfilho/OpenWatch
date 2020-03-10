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
#include "ntpInterface.h"
#include "../icons.h"

NtpInterface::NtpInterface() : useRTC(false), screenPos(POSITION_BAR_BOTTOM)
{
}

bool NtpInterface::setup()
{
    WatchInterface::setup();
    msgToDisplay = "Press B: Start";
    started = false;
    return false;
}

bool NtpInterface::loop()
{
    WatchInterface::loop();
    frameTemplate("NTP > RTC", msgToDisplay, icon_gears);
    // Check if connection is ready to start update
    if (started && network.isConnect())
        startUpdate();
    return true;
}

void NtpInterface::startUpdate()
{
    started = false;
    msgToDisplay = "Updating...";
    loop();
    ntpUtils.begin();
    ntpUtils.update();
    ntpUtils.end();
    msgToDisplay = "Updated!";
    loop();
    network.end();
    wakeupTime = millis();
    noSleep = false;
}

void NtpInterface::pressB(byte count)
{
    started = true;
    noSleep = true;
    network.begin();
}

void NtpInterface::finish()
{
    WatchInterface::finish();
    noSleep = false;
    network.end();
}
