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
#ifndef __CONFIG_H_
#define __CONFIG_H_
#include <ArduinoJson.h>

/** Screen default rotation */
#define SCREEN_ROTATION 3

/** Maximum screen brightness */
#define SCREEN_BRIGHTNESS 8

/** Number of seconds without interaction to enter in deepSleep */
#define SCREEN_WAKEUP_TIMEOUT 20 * 1000

/** Delay between update time in watch screen interface */
#define REFRESH_TIME 1000

/** Definitions for Battery Measure */
#define MAX_VOLTAGE 4.1
#define MIN_VOLTAGE 3.40

/** Network definitions */
#define NETWORK_CONNECTION_TIMEOUT 5000
#define NETWORK_CONNECTION_DELAY 100

class Config
{
private:
    byte _config_changed;

public:
    StaticJsonDocument<2048> jsonConfig;
    byte screen_brightness;
    byte screen_watchInterface;
    unsigned int network_connection_timeout;
    unsigned int screen_refreshTime;
    unsigned long screen_wakeup_timeout;
    Config();
    void begin();
    void setScreenBrightness(byte value);
    void setWatchInterface(byte value);
    void nextWatchInterface(void);
    void nextScreenBrightness(void);
    void save(void);
    void load(void);
    int existsNetwork(String name);
    String getNetworkPassword(String name);
    String getNTPServer();
    int getNTPOffset();
};

#endif