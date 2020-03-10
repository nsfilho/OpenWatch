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
unsigned long lastPressA = 0;
unsigned long lastPressB = 0;
byte countPressA = 0;
byte countPressB = 0;

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
    M5.update();

    /** Button A: Key pressed */
    if (M5.BtnA.wasPressed() != 0)
    {
        countPressA++;
        wakeupTime = millis();
        lastPressA = millis();
    }
    else if (countPressA > 0 && millis() - lastPressA > BUTTON_COUNT_TIMEOUT)
    {
        interfaces.pressA(countPressA);
        countPressA = 0;
        lastPressA = 0;
    }

    /** Button B: Key pressed */
    if (M5.BtnB.wasPressed() != 0)
    {
        countPressB++;
        wakeupTime = millis();
        lastPressB = millis();
    }
    else if (countPressB > 0 && millis() - lastPressB > BUTTON_COUNT_TIMEOUT)
    {
        interfaces.pressB(countPressB);
        countPressB = 0;
        lastPressB = 0;
    }
    interfaces.loop();
    network.loop();
    ntpUtils.loop();
    check_wakeup_timeout();
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
