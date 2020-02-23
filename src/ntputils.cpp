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
#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include "main.h"
#include "ntputils.h"
#include "rtcutils.h"

WiFiUDP ntpUDP;

NTPUtils::NTPUtils()
{
    active = false;
}

void NTPUtils::begin()
{
    active = true;
}

void NTPUtils::update()
{
    server = strdup(config.getNTPServer().c_str());
    NTPClient client = NTPClient(ntpUDP, server, config.getNTPOffset());
    if (client.forceUpdate())
    {
        // Serial.print("NTP result: ");
        // Serial.println(client.getFormattedDate());
        setRTC_fromNTP(client.getFormattedDate());
    }
    free(server);
}

void NTPUtils::force()
{
}

void NTPUtils::loop()
{
}

void NTPUtils::end()
{
    active = false;
}