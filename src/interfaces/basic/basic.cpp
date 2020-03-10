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
#include "basic.h"
#include "rtcutils.h"

BasicInterface::BasicInterface() : batteryPos(POSITION_BAR_BOTTOM), screenPos(POSITION_BAR_TOP)
{

}

bool BasicInterface::loop()
{
    WatchInterface::loop();
    tftSprite.fillSprite(BLACK);
    tftSprite.setTextSize(1);
    tftSprite.setTextColor(WHITE);
    tftSprite.setCursor(10, 15, 4);
    tftSprite.printf("%02d:%02d:%02d", RTC_TimeStruct.Hours, RTC_TimeStruct.Minutes, RTC_TimeStruct.Seconds);
    tftSprite.setCursor(10, 45, 4);
    tftSprite.printf("%02d/%02d/%02d", RTC_DateStruct.Date, RTC_DateStruct.Month, RTC_DateStruct.Year);
    return true;
}
