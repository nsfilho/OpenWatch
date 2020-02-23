#include "main.h"
#include "basic.h"
#include "rtcutils.h"

BasicInterface::BasicInterface()
{
    batteryPos = POSITION_BAR_BOTTOM;
    screenPos = POSITION_BAR_TOP;
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