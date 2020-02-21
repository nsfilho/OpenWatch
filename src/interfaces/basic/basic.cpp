#include <M5StickC.h>
#include "main.h"
#include "basic.h"
#include "rtcutils.h"

int myFont = 1;

bool BasicInterface::setup()
{
    WatchInterface::setup();
    batteryPos = POSITION_BAR_BOTTOM;
    screenPos = POSITION_BAR_TOP;
    return false;
}

bool BasicInterface::loop()
{
    tftSprite.fillSprite(BLACK);
    WatchInterface::loop();
    tftSprite.setTextSize(1);
    tftSprite.setTextColor(WHITE);
    tftSprite.setCursor(10, 15, 4);
    tftSprite.printf("%02d:%02d:%02d", RTC_TimeStruct.Hours, RTC_TimeStruct.Minutes, RTC_TimeStruct.Seconds);
    tftSprite.setCursor(10, 45, 4);
    tftSprite.printf("%02d/%02d/%02d", RTC_DateStruct.Date, RTC_DateStruct.Month, RTC_DateStruct.Year);
    return true;
}