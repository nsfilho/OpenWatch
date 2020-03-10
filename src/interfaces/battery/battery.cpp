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
#include "battery.h"
#include "batteryImgs.h"

BatteryInterface::BatteryInterface(): useRTC(false), screenPos(POSITION_BAR_LEFT)
{
}

bool BatteryInterface::setup()
{
    WatchInterface::setup(WHITE);
    M5.Axp.EnableCoulombcounter();
    return false;
}

void BatteryInterface::finish()
{
    WatchInterface::finish();
    M5.Axp.DisableCoulombcounter();
}

bool BatteryInterface::loop()
{
    WatchInterface::loop();
    tftSprite.fillSprite(WHITE);
    float voltage, current;
    String tipo = "Battery";
    byte batteryLvl = BATTERY_LVL;
    if (M5.Axp.GetVBusVoltage() > 4)
    {
        // USB Connected
        tipo = "USB";
        voltage = M5.Axp.GetVBusVoltage();
        current = M5.Axp.GetVBusCurrent();
    }
    else if (M5.Axp.GetVinVoltage() > 3)
    {
        // 5V-In connected
        tipo = "External";
        voltage = M5.Axp.GetVinVoltage();
        current = M5.Axp.GetVinCurrent();
    }
    else
    {
        // Battery
        voltage = M5.Axp.GetBatVoltage();
        current = M5.Axp.GetBatCurrent();
    }
    tftSprite.setTextColor(BLACK);
    tftSprite.setCursor(13, 10, 2);
    tftSprite.setTextSize(2);
    tftSprite.print(tipo);
    tftSprite.setTextSize(1);
    tftSprite.setCursor(13, 45);
    tftSprite.printf("V: %.3fv", voltage);
    tftSprite.setCursor(13, 60);
    tftSprite.printf("I: %.3fma\r\n", current);
    if (batteryLvl > 80)
        tftSprite.pushImage(120, 0, 40, 80, batteryStatus6);
    else if (batteryLvl > 60)
        tftSprite.pushImage(120, 0, 40, 80, batteryStatus5);
    else if (batteryLvl > 40)
        tftSprite.pushImage(120, 0, 40, 80, batteryStatus4);
    else if (batteryLvl > 20)
        tftSprite.pushImage(120, 0, 40, 80, batteryStatus3);
    else if (batteryLvl > 0)
        tftSprite.pushImage(120, 0, 40, 80, batteryStatus2);
    else
        tftSprite.pushImage(120, 0, 40, 80, batteryStatus1);
    return true;
}
