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
#ifndef __WATCH_INTERFACE_H_
#define __WATCH_INTERFACE_H_

#include <M5StickC.h>
#include "config.h"
#include "network.h"

#define SCREEN_BAR_WIDTH(X) (((millis() - wakeupTime) * X) / config.screen_wakeup_timeout)
#define BATTERY_BAR_WIDTH(X) (((M5.Axp.GetBatVoltage() - MIN_VOLTAGE) * X) / (MAX_VOLTAGE - MIN_VOLTAGE))
#define BATTERY_LVL ((M5.Axp.GetBatVoltage() - MIN_VOLTAGE) / (MAX_VOLTAGE - MIN_VOLTAGE)) * 100

#define NETWORK_STATUS_DIALOG_TIMEOUT 3000

typedef enum
{
    POSITION_BAR_TOP = 0,
    POSITION_BAR_RIGHT = 1,
    POSITION_BAR_BOTTOM = 2,
    POSITION_BAR_LEFT = 3,
    POSITION_BAR_OFF = 4
} display_position_t;

typedef enum
{
    NETWORK_STATUS_NONE = 0,
    NETWORK_STATUS_DIALOG = 1,
    NETWORK_STATUS_SMALL_TOP_RIGHT = 2,
    NETWORK_STATUS_SMALL_TOP_LEFT = 3,
    NETWORK_STATUS_SMALL_BOTTOM_RIGHT = 4,
    NETWORK_STATUS_SMALL_BOTTOM_LEFT = 5,
} display_network_status_t;

typedef enum
{
    PERIOD_MORNING = 0,
    PERIOD_AFTERNOON = 1,
    PERIOD_EVENING = 2,
} day_period_t;

class WatchInterface
{
private:
    watch_network_status_t lastNetworkStatus = WN_OFF;
    unsigned long lastNetworkStatusTime = 0;
    bool loopNetworkSmall();
    bool loopNetworkDialog();
    bool loopBatteryBar();
    bool loopScreenBar();
    bool loopNetwork();

protected:
    display_position_t batteryPos = POSITION_BAR_OFF;
    display_position_t screenPos = POSITION_BAR_OFF;
    display_network_status_t networkStatus = NETWORK_STATUS_DIALOG;
    virtual bool loop();

public:
    bool noSleep = false;

    /** 
     * Setup a watch interface
     * Return: if true, push tftSprite to LCD.
    */
    virtual bool setup(uint32_t color);
    virtual bool setup();

    /**
     * Looping interface
     * Return: if true, push tftSprite to LCD.
     */
    virtual bool loopStatus();
    virtual void finish();
    virtual void pressA();
    virtual void pressB();
};

#endif
