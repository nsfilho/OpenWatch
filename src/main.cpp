/**
 * Main Framework File
 */
#undef DEBUG_WATCH

#include <M5StickC.h>
#include <WiFi.h>
#include "main.h"
#include "rtcutils.h"

/** Instantiate the shared class and objects */
Config config = Config();
Interfaces interfaces = Interfaces();
TFT_eSprite tftSprite = TFT_eSprite(&M5.Lcd);
NTPUtils ntpUtils = NTPUtils();
Network network = Network();

/** Controls variables */
unsigned long wakeupTime = 0;  // Contains wake up (from sleep) millis
unsigned long lastRefresh = 0; // Control last watchInterface refresh

/**
 * Main Setup - Executed after PowerOn and DeepSleep.
 */
void setup(void)
{
    M5.begin(true, true, true);
    M5.Lcd.fillScreen(BLACK);
    tftSprite.setColorDepth(16);
    tftSprite.createSprite(160, 80);
    // setRTC_fromCompiler();
    config.begin();
    interfaces.begin();
    M5.Axp.ScreenBreath(config.screen_brightness);
    interfaces.setupInterface();
    wakeupTime = millis();
    lastRefresh = millis();
    WiFi.disconnect(true);
#ifdef DEBUG_WATCH
    Serial.println("End of setup");
#endif
}

void loop(void)
{
    bool updateSprite = false;
    M5.update();

    /** Button A: Key pressed */
    if (M5.BtnA.wasPressed() != 0)
    {
#ifdef DEBUG_WATCH
        Serial.println("ButtonA: Pressed");
#endif
        wakeupTime = millis();
        interfaces.pressA();
    }

    /** Button B: Key pressed */
    if (M5.BtnB.wasPressed() != 0)
    {
#ifdef DEBUG_WATCH
        Serial.println("ButtonB: Pressed");
#endif
        wakeupTime = millis();
        interfaces.pressB();
    }
    updateSprite = update_watch_interface() || updateSprite;
    updateSprite = network.loop(interfaces.getCurrent()->displayNetworkStatus) || updateSprite;
    ntpUtils.loop();
    if (updateSprite)
        tftSprite.pushSprite(0, 0);
    check_wakeup_timeout();
}

/**
 * Routine to update the watch screen interface (time)
 */
bool update_watch_interface(void)
{
    bool result = false;
    if (millis() - lastRefresh > config.screen_refreshTime)
    {
#ifdef DEBUG_WATCH
        Serial.print(millis());
        Serial.print(": Refreshing watch interface: ");
        Serial.print(config.screen_watchInterface);
        Serial.print(" / ");
        Serial.println(interfaces.totalInterfaces - 1);
#endif
        getRTC_info();
        result = interfaces.loopInterface();
        lastRefresh = millis();
    }
    return result;
}

/**
 * Check if is the time to sleep
 */
void check_wakeup_timeout(void)
{
    if (config.noSleep)
        return;

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
