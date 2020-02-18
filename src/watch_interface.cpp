/**
 * This file define a base structure for a watch interface
 */
#include <M5StickC.h>
#include "watch_interface.h"
#include "main.h"

bool WatchInterface::setup()
{
    M5.Lcd.setRotation(SCREEN_ROTATION);
    tftSprite.setRotation(SCREEN_ROTATION);
    return false;
}

/**
 * Return true if your code buffer all display info in Sprite.
 */
bool WatchInterface::loop()
{
    // do nothing
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
