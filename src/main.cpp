#include <M5StickC.h>
#include "config.h"
#include "main.h"
#include "rtcutils.h"
#include "nixietube/nixietube.h"

byte watchInterface = 0;       // Which watch interface to render
unsigned long wakeupTime = 0;  // Contains wake up (from sleep) millis
unsigned long lastRefresh = 0; // Control last watchInterface refresh

void setup(void)
{
    M5.begin();
    M5.Lcd.fillScreen(BLACK);
    M5.Axp.ScreenBreath(SCREEN_BRIGHTNESS); // 7-15
    lastRefresh = millis();
    // setRTC_fromCompiler();
    wakeupTime = millis();
}

void loop(void)
{
    M5.update();
    if (M5.BtnA.wasPressed() != 0)
    {
        watchInterface = (watchInterface == 3 ? 1 : watchInterface + 1);
        M5.Lcd.fillScreen(BLACK);
        change_watch_interface();
        wakeupTime = millis();
    }
    update_watch_interface();
    check_wakeup_timeout();
}

/**
 * Setup a new watch interface
 */
void change_watch_interface(void)
{
    switch (watchInterface)
    {
    case 1:
    case 2:
    case 3:
        nixietube_setup();
        break;
    }
}

/**
 * Start a routine to update the watch screen interface (time)
 */
void update_watch_interface(void)
{
    if (millis() - lastRefresh > REFRESH_TIME)
    {
        getRTC_info();
        switch (watchInterface)
        {
        case 1:
            nixietube_1_line();
            break;
        case 2:
            nixietube_2_line();
            break;
        case 3:
            nixietube_3_line();
            break;
        }
        lastRefresh = millis();
    }
}

/**
 * Check if is the time to sleep
 */
void check_wakeup_timeout(void)
{
    if (millis() - wakeupTime > SCREEN_WAKEUP_TIMEOUT)
    {
        M5.Axp.LightSleep(0);
    }
}
