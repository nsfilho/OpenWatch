#include <M5StickC.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include "main.h"
#include "interfaces/interfaces.h"

#define DEBUG_WATCH 1

StaticJsonDocument<512> doc;

Config::Config()
{
    screen_watchInterface = 0;
    screen_brightness = SCREEN_BRIGHTNESS;
    screen_wakeup_timeout = SCREEN_WAKEUP_TIMEOUT;
    screen_refreshTime = REFRESH_TIME;
    noSleep = false;
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
#ifdef DEBUG_WATCH
        serializeJsonPretty(doc, Serial);
#endif
        config.close();
    }
}

int Config::existsNetwork(String name)
{
    JsonArray wifis = doc["wifi"];
    for (int x = 0; x < wifis.size(); x++)
    {
        JsonVariant wifi_config = wifis.getElement(x);
        const char *wifi_ssid = wifi_config["ssid"].as<char *>();
#ifdef DEBUG_WATCH
        Serial.print("     ");
        Serial.print(x);
        Serial.print(": Comparing: [");
        Serial.print(name);
        Serial.print("] with [");
        Serial.print(wifi_ssid);
        Serial.println("]");
#endif
        if (strcmp(name.c_str(), wifi_ssid) == 0)
            return x;
    }
    return -1;
}

String Config::getNetworkPassword(String name)
{
    JsonArray wifis = doc["wifi"];
    int network_index = existsNetwork(name);
    if (network_index > -1)
    {
        JsonVariant wifi_config = wifis.getElement(network_index);
        return wifi_config["password"].as<String>();
    }
    return String();
}