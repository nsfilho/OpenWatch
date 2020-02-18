#include <M5StickC.h>
#include "main.h"
#include "basic.h"
#include "rtcutils.h"

int myFont = 1;

bool BasicInterface::setup()
{
    M5.Lcd.setRotation(SCREEN_ROTATION);
    tftSprite.setRotation(SCREEN_ROTATION);
    tftSprite.fillScreen(BLACK);
    return false;
}

bool BasicInterface::loop()
{
    tftSprite.fillSprite(BLACK);
    tftSprite.setTextSize(1);
    tftSprite.setTextColor(WHITE);
    tftSprite.setCursor(10, 15, 4);
    tftSprite.printf("%02d:%02d:%02d", RTC_TimeStruct.Hours, RTC_TimeStruct.Minutes, RTC_TimeStruct.Seconds);
    tftSprite.setCursor(10, 45, 4);
    tftSprite.printf("%02d/%02d/%02d", RTC_DateStruct.Date, RTC_DateStruct.Month, RTC_DateStruct.Year);

    // Bar to deep sleep (on bottom)
    byte barWidth = (millis() - wakeupTime) * 160 / config.screen_wakeup_timeout;
    tftSprite.fillRect(0, 80 - 3, 160 - barWidth, 80, RED);

    // Battery Bar (on top)
    barWidth = ((M5.Axp.GetBatVoltage() - MIN_VOLTAGE) / (MAX_VOLTAGE - MIN_VOLTAGE)) * 160;
    tftSprite.fillRect(0, 0, barWidth, 3, GREEN);

    return true;
}