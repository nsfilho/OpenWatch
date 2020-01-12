#include <M5StickC.h>
#include "config.h"
#include "main.h"
#include "watch_interface.h"
#include "rtcutils.h"
#include "nixietube/nixietube.h"
#include "battery/battery.h"

#define DEBUG_WATCH

TFT_eSprite tftSprite = TFT_eSprite(&M5.Lcd);

NixieTube1 i1 = NixieTube1();
NixieTube2 i2 = NixieTube2();
NixieTube3 i3 = NixieTube3();
Battery i4 = Battery();

#define WATCH_NTERFACES 4
WatchInterface *interfaces[] = {&i1, &i2, &i3, &i4};

unsigned long wakeupTime = 0;  // Contains wake up (from sleep) millis
unsigned long lastRefresh = 0; // Control last watchInterface refresh

void setup(void)
{
    M5.begin(true, true, true);
    M5.Lcd.fillScreen(BLACK);
    M5.Axp.ScreenBreath(SCREEN_BRIGHTNESS); // 7-15
    tftSprite.createSprite(160, 80);
    // setRTC_fromCompiler();
    interfaces[watchInterface]->setup();
    wakeupTime = millis();
    lastRefresh = millis();
#ifdef DEBUG_WATCH
    Serial.println("End of setup");
#endif
}

void loop(void)
{
    M5.update();
    if (M5.BtnA.wasPressed() != 0)
    {
#ifdef DEBUG_WATCH
        Serial.println("ButtonA: Pressed");
#endif
        wakeupTime = millis();
        interfaces[watchInterface]->pressA();
    }
    if (M5.BtnB.wasPressed() != 0)
    {
#ifdef DEBUG_WATCH
        Serial.println("ButtonB: Pressed");
#endif
        wakeupTime = millis();
        interfaces[watchInterface]->pressB();
    }
    update_watch_interface();
    check_wakeup_timeout();
}

/**
 * Setup a new watch interface
 */
void change_watch_interface()
{
    interfaces[watchInterface]->finish();
    watchInterface = (watchInterface == WATCH_NTERFACES - 1 ? 0 : watchInterface + 1);
    interfaces[watchInterface]->setup();
}

/**
 * Start a routine to update the watch screen interface (time)
 */
void update_watch_interface(void)
{
    if (millis() - lastRefresh > REFRESH_TIME)
    {
#ifdef DEBUG_WATCH
        Serial.print(millis());
        Serial.print(": Refreshing watch interface: ");
        Serial.println(watchInterface);
#endif
        getRTC_info();
        interfaces[watchInterface]->loop();
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
#ifdef DEBUG_WATCH
        Serial.println("Entering in Deep Sleep!");
#endif

        wakeupTime = millis();
        M5.Axp.DeepSleep();
    }
}
