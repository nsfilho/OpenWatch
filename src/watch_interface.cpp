/**
 * This file define a base structure for a watch interface
 */
#include <M5StickC.h>
#include "watch_interface.h"
#include "main.h"

void WatchInterface::setup()
{
    M5.Lcd.setRotation(3);
}

void WatchInterface::loop()
{
    // do nothing
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
