#include <M5StickC.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include "main.h"
#include "interfaces/interfaces.h"

StaticJsonDocument<512> doc;

Config::Config()
{
    screen_watchInterface = 0;
    screen_brightness = SCREEN_BRIGHTNESS;
    screen_wakeup_timeout = SCREEN_WAKEUP_TIMEOUT;
    screen_refreshTime = REFRESH_TIME;
}

void Config::begin()
{
    load();
    M5.Axp.ScreenBreath(screen_brightness);
    _config_changed = 0;
    Serial.println("Config: Loaded!");
}

void Config::setScreenBrightness(byte value)
{
    if (screen_brightness != value)
    {
        _config_changed = 1;
        screen_brightness = value;
        M5.Axp.ScreenBreath(screen_brightness);
    }
}

void Config::setWatchInterface(byte value)
{
    if (screen_watchInterface != value)
    {
        _config_changed = 1;
        interfaces.finishInterface();
        screen_watchInterface = value;
        interfaces.setupInterface();
        interfaces.loopInterface();
    }
}

void Config::nextScreenBrightness()
{
    setScreenBrightness(screen_brightness < 12 ? screen_brightness + 1 : 7);
}

void Config::nextWatchInterface()
{
    _config_changed = 1;
    setWatchInterface(screen_watchInterface < interfaces.totalInterfaces - 1 ? screen_watchInterface + 1 : 0);
}

void Config::load()
{
    if (!SPIFFS.begin(true))
    {
        Serial.println("SPIFFS failed!");
        return;
    }
    fs::File config = SPIFFS.open("/config.json");
    DeserializationError error = deserializeJson(doc, config);
    if (error)
        Serial.println(F("Failed to read file!"));
    screen_watchInterface = doc["screen"]["watchInterface"] | 0;
    screen_refreshTime = doc["screen"]["refreshTime"] | REFRESH_TIME;
    screen_brightness = doc["screen"]["brightness"] | SCREEN_BRIGHTNESS;
    screen_wakeup_timeout = doc["screen"]["wakeupTimeout"] | SCREEN_WAKEUP_TIMEOUT;
    config.close();
}

void Config::save()
{
    if (_config_changed)
    {
        fs::File config = SPIFFS.open("/config.json", "w");
        doc["screen"]["watchInterface"] = screen_watchInterface;
        doc["screen"]["brightness"] = screen_brightness;
        doc["screen"]["refreshTime"] = screen_refreshTime;
        doc["screen"]["wakeupTimeout"] = screen_wakeup_timeout;
        serializeJson(doc, config);
        config.close();
    }
}