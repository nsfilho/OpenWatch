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
#include <M5StickC.h>
#include "watch_interface.h"
#include "main.h"
#include "rtcutils.h"

/** Instantiate the shared class and objects */
Config config = Config();
Interfaces interfaces = Interfaces();
TFT_eSprite tftSprite = TFT_eSprite(&M5.Lcd);
NTPUtils ntpUtils = NTPUtils();
Network network = Network();

/** Controls variables */
unsigned long wakeupTime = 0;  // Contains wake up (from sleep) millis
unsigned long lastRefresh = 0; // Control last watchInterface refresh

/**
 * Main Setup - Executed after PowerOn and DeepSleep.
 */
void setup(void)
{
    M5.begin(true, true, true);
    initScreen();
    // setRTC_fromCompiler();
    config.begin();
    interfaces.begin();
    network.end();
    interfaces.setupInterface();
    M5.Axp.ScreenBreath(config.screen_brightness);
    wakeupTime = millis();
    lastRefresh = millis();
}

void initScreen(void)
{
    tftSprite.setColorDepth(16);
    tftSprite.createSprite(160, 80);
    tftSprite.fillSprite(BLACK);
    tftSprite.pushSprite(0, 0);
}

void loop(void)
{
    bool updateSprite = false;
    M5.update();

    /** Button A: Key pressed */
    if (M5.BtnA.wasPressed() != 0)
    {
        wakeupTime = millis();
        interfaces.pressA();
    }

    /** Button B: Key pressed */
    if (M5.BtnB.wasPressed() != 0)
    {
        wakeupTime = millis();
        interfaces.pressB();
    }
    updateSprite = update_watch_interface();
    network.loop();
    ntpUtils.loop();
    if (updateSprite)
        tftSprite.pushSprite(0, 0);
    check_wakeup_timeout();
}

/**
 * Routine to update the watch screen interface (time)
 */
bool update_watch_interface(void)
{
    bool result = false;
    if (millis() - lastRefresh > config.screen_refreshTime)
    {
        getRTC_info();
        result = interfaces.loopInterface();
        lastRefresh = millis();
    }
    return result;
}

/**
 * Check if is the time to sleep
 */
void check_wakeup_timeout(void)
{
    if (interfaces.getCurrent()->noSleep)
        return;

    if (millis() - wakeupTime > config.screen_wakeup_timeout)
    {
        config.save();
        M5.Axp.DeepSleep();
    }
}
