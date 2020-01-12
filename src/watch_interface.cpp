/**
 * This file define a base structure for a watch interface
 */
#include <M5StickC.h>
#include "main.h"
#include "config.h"
#include "watch_interface.h"

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
    change_watch_interface();
}


void WatchInterface::pressB()
{
    // normally used to start config menu (for watch interface)
    screen_brightness = (screen_brightness < 12) ? screen_brightness + 1 : 7;
    M5.Axp.ScreenBreath(screen_brightness);
}
