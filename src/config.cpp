/**
 * Openwatch Framework
 * Copyright (C) 2020  Nelio Souza Santos Filho <nsfilho@icloud.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>. 
 *
 */
#include <M5StickC.h>
#include <SPIFFS.h>
#include "main.h"
#include "interfaces/interfaces.h"

/**
 * Create a new instance of Config Class
 */
Config::Config()
{
    screen_watchInterface = 0;
    screen_brightness = SCREEN_BRIGHTNESS;
    screen_wakeup_timeout = SCREEN_WAKEUP_TIMEOUT;
    screen_refreshTime = REFRESH_TIME;
    network_connection_timeout = NETWORK_CONNECTION_TIMEOUT;
}

/**
 * After instantiate, set the basics
 */
void Config::begin()
{
    load();
    _config_changed = 0;
#ifdef DEBUG_WATCH
    Serial.println("Config: Loaded!");
    serializeJsonPretty(jsonConfig, Serial);
#endif
}

/**
 * Configure the screen brightness and save.
 */
void Config::setScreenBrightness(byte value)
{
    if (screen_brightness != value)
    {
        _config_changed = 1;
        screen_brightness = value;
        M5.Axp.ScreenBreath(screen_brightness);
    }
}

/**
 * Set the current Watch Interface and save.
 * After wakeup from deepSleep or powerOn load the last interface saved.
 */
void Config::setWatchInterface(byte value)
{
    if (screen_watchInterface != value)
    {
        bool updateSprite = false;
        _config_changed = 1;
        interfaces.finishInterface();
        screen_watchInterface = value;
        updateSprite = interfaces.setupInterface() || updateSprite;
        updateSprite = interfaces.loopInterface() || updateSprite;
        if (updateSprite)
            tftSprite.pushSprite(0, 0);
    }
}

/**
 * Simple sugar to continuous change the screen brightness levels.
 */
void Config::nextScreenBrightness()
{
    setScreenBrightness(screen_brightness < 12 ? screen_brightness + 1 : 7);
}

/**
 * Simple sugar to continues change (rotate) watch interfaces
 */
void Config::nextWatchInterface()
{
    _config_changed = 1;
    setWatchInterface(screen_watchInterface < interfaces.totalInterfaces - 1 ? screen_watchInterface + 1 : 0);
}

/**
 * Load the config file from SPIFFS ('/config.json') and parse it.
 */
void Config::load()
{
    if (!SPIFFS.begin(true))
    {
        Serial.println("SPIFFS failed!");
        return;
    }
    fs::File config = SPIFFS.open("/config.json");
    DeserializationError error = deserializeJson(jsonConfig, config);
    if (error)
        Serial.println(F("Failed to read file!"));

    // Save for quick access the most used configurations.
    screen_watchInterface = jsonConfig["screen"]["watchInterface"] | 0;
    screen_refreshTime = jsonConfig["screen"]["refreshTime"] | REFRESH_TIME;
    screen_brightness = jsonConfig["screen"]["brightness"] | SCREEN_BRIGHTNESS;
    screen_wakeup_timeout = jsonConfig["screen"]["wakeupTimeout"] | SCREEN_WAKEUP_TIMEOUT;
    network_connection_timeout = jsonConfig["network"]["connectionTimeout"] | NETWORK_CONNECTION_TIMEOUT;
    config.close();
}

/**
 * Save all configurations to SPIFFs file ('/config.json').
 */
void Config::save()
{
    if (_config_changed)
    {
        fs::File config = SPIFFS.open("/config.json", "w");
        jsonConfig["screen"]["watchInterface"] = screen_watchInterface;
        jsonConfig["screen"]["brightness"] = screen_brightness;
        jsonConfig["screen"]["refreshTime"] = screen_refreshTime;
        jsonConfig["screen"]["wakeupTimeout"] = screen_wakeup_timeout;
        serializeJson(jsonConfig, config);
#ifdef DEBUG_WATCH
        serializeJsonPretty(jsonConfig, Serial);
#endif
        config.close();
    }
}

/**
 * Check if it's a know network and return the index.
 */
int Config::existsNetwork(String name)
{
    JsonArray wifis = jsonConfig["wifi"];
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

/**
 * Take a password from a knows network
 */
String Config::getNetworkPassword(String name)
{
    JsonArray wifis = jsonConfig["wifi"];
    int network_index = existsNetwork(name);
    if (network_index > -1)
    {
        JsonVariant wifi_config = wifis.getElement(network_index);
        return wifi_config["password"].as<String>();
    }
    return String();
}

/**
 * Get the NTP Server to connected.
 */
String Config::getNTPServer()
{
    return jsonConfig["ntp"]["server"];
}

/**
 * Get the Timezone (Offset) in minutes (positive or negative)
 */
int Config::getNTPOffset()
{
    return jsonConfig["ntp"]["offset"];
}
