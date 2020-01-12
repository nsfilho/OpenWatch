#define DEBUG_WATCH

#include <M5StickC.h>
#include <WiFi.h>
#include "main.h"
#include "rtcutils.h"

Config config = Config();
Interfaces interfaces = Interfaces();
TFT_eSprite tftSprite = TFT_eSprite(&M5.Lcd);

unsigned long wakeupTime = 0;  // Contains wake up (from sleep) millis
unsigned long lastRefresh = 0; // Control last watchInterface refresh

void setup(void)
{
    M5.begin(true, true, true);
    M5.Lcd.fillScreen(BLACK);
    tftSprite.createSprite(160, 80);
    // setRTC_fromCompiler();
    config.begin();
    interfaces.begin();
    interfaces.setupInterface();
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
        interfaces.pressA();
    }
    if (M5.BtnB.wasPressed() != 0)
    {
#ifdef DEBUG_WATCH
        Serial.println("ButtonB: Pressed");
#endif
        wakeupTime = millis();
        interfaces.pressB();
    }
    update_watch_interface();
    check_wakeup_timeout();
}

/**
 * Start a routine to update the watch screen interface (time)
 */
void update_watch_interface(void)
{
    if (millis() - lastRefresh > config.screen_refreshTime)
    {
#ifdef DEBUG_WATCH
        Serial.print(millis());
        Serial.print(": Refreshing watch interface: ");
        Serial.print(config.screen_watchInterface);
        Serial.print(" / ");
        Serial.println(interfaces.totalInterfaces);
#endif
        getRTC_info();
        interfaces.loopInterface();
        lastRefresh = millis();
    }
}

/**
 * Check if is the time to sleep
 */
void check_wakeup_timeout(void)
{
    if (millis() - wakeupTime > config.screen_wakeup_timeout)
    {
#ifdef DEBUG_WATCH
        Serial.println("Entering in Deep Sleep!");
#endif
        config.save();
        wakeupTime = millis();
        M5.Axp.DeepSleep();
    }
}
