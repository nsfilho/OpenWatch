/**
 * This file define a base structure for a watch interface
 */
#include <M5StickC.h>
#include "watch_interface.h"
#include "main.h"

#define SCREEN_BAR_WIDTH(X) (((millis() - wakeupTime) * X) / config.screen_wakeup_timeout)
#define BATTERY_BAR_WIDTH(X) (((M5.Axp.GetBatVoltage() - MIN_VOLTAGE) * X) / (MAX_VOLTAGE - MIN_VOLTAGE))

bool WatchInterface::setup()
{
    M5.Lcd.setRotation(SCREEN_ROTATION);
    tftSprite.setRotation(SCREEN_ROTATION);
    displayNetworkStatus = true;
    noSleep = false;
    batteryPos = POSITION_BAR_OFF;
    screenPos = POSITION_BAR_OFF;
    return false;
}

/**
 * Return true if your code buffer all display info in Sprite.
 */
bool WatchInterface::loop()
{
    // do nothing
    loopBatteryBar();
    loopScreenBar();
    return false;
}

void WatchInterface::finish()
{
    // do nothing
}

void WatchInterface::pressA()
{
    config.nextWatchInterface();
}

void WatchInterface::pressB()
{
    // normally used to start config menu (for watch interface)
    config.nextScreenBrightness();
}

void WatchInterface::loopBatteryBar()
{
    switch (batteryPos)
    {
    case POSITION_BAR_TOP:
        tftSprite.fillRect(0, 1, BATTERY_BAR_WIDTH(160), 4, GREEN);
        break;
    case POSITION_BAR_BOTTOM:
        tftSprite.fillRect(0, 77, BATTERY_BAR_WIDTH(160), 80, GREEN);
        break;
    case POSITION_BAR_LEFT:
        tftSprite.fillRect(0, 0, 3, BATTERY_BAR_WIDTH(80), GREEN);
        break;
    case POSITION_BAR_RIGHT:
        tftSprite.fillRect(77, 0, 80, BATTERY_BAR_WIDTH(80), GREEN);
        break;
    }
}

void WatchInterface::loopScreenBar()
{
    switch (screenPos)
    {
    case POSITION_BAR_TOP:
        tftSprite.fillRect(0, 1, 160 - SCREEN_BAR_WIDTH(160), 4, RED);
        break;
    case POSITION_BAR_BOTTOM:
        tftSprite.fillRect(0, 77, 160 - SCREEN_BAR_WIDTH(160), 80, RED);
        break;
    case POSITION_BAR_LEFT:
        tftSprite.fillRect(0, 0, 3, SCREEN_BAR_WIDTH(80), RED);
        break;
    case POSITION_BAR_RIGHT:
        tftSprite.fillRect(77, 0, 80, SCREEN_BAR_WIDTH(80), RED);
        break;
    }
}