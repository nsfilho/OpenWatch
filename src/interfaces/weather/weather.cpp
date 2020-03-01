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
#include <HTTPClient.h>
#include "main.h"
#include "weather.h"
#include "weatherImgs.h"
#include "rtcutils.h"

#define DEBUG_WATCH 1

bool updated = false;
byte cityIndex;
byte statusInfo = 0;
long lastStatusInfo = 0;
JsonArray cities;

WeatherInterface::WeatherInterface()
{
    networkStatus = NETWORK_STATUS_SMALL_TOP_RIGHT;
}

bool WeatherInterface::setup()
{
    WatchInterface::setup();
    cityIndex = config.jsonConfig["openWeather"]["index"];
    cities = config.jsonConfig["openWeather"]["cities"];
    lastStatusInfo = millis();
    if (needUpdate())
        startUpdate();
    return false;
}

void WeatherInterface::startUpdate()
{
    noSleep = true;
    updated = false;
    network.begin();
}

bool WeatherInterface::needUpdate()
{
    JsonVariant city = cities[cityIndex];
    const long lastRead = city["lastRead"];
    return getRTC_EllapsedTime(&RTC_DateStruct, &RTC_TimeStruct) - lastRead > 3600;
}

void WeatherInterface::updateInfo()
{
    if (!updated && network.isConnect())
    {
        JsonVariant city = cities[cityIndex];
        String appId = config.jsonConfig["openWeather"]["appid"];
        String units = config.jsonConfig["openWeather"]["units"];
        String cityName = city["name"];
        HTTPClient http;
        String url = "http://api.openweathermap.org/data/2.5/weather?q=" + cityName + "&appid=" + appId + "&units=" + units;
        http.begin(url);
        const int httpCode = http.GET();
        if (httpCode == 200)
        {
            DynamicJsonDocument weatherInfo(512);
            const String jsonAnswer = http.getString();
#ifdef DEBUG_WATCH
            Serial.println("JSON Answer:");
            Serial.println(jsonAnswer);
#endif
            deserializeJson(weatherInfo, jsonAnswer);
            city["temp"] = weatherInfo["main"]["temp"];
            city["temp_min"] = weatherInfo["main"]["temp_min"];
            city["temp_max"] = weatherInfo["main"]["temp_max"];
            city["pressure"] = weatherInfo["main"]["pressure"];
            city["humidity"] = weatherInfo["main"]["humidity"];
            city["status"] = weatherInfo["weather"][0]["description"];
            city["lastRead"] = getRTC_EllapsedTime(&RTC_DateStruct, &RTC_TimeStruct);
            city["rain3h"] = weatherInfo["rain"]["3h"];
            Serial.println("Updated weather info");
            config.save();
        }
        http.end();
        network.end();
        updated = true;
        noSleep = false;
    }
}

bool WeatherInterface::loop()
{
    WatchInterface::loop();
    updateInfo();

    tftSprite.fillSprite(BLACK);
    tftSprite.setTextFont(2);
    tftSprite.setTextSize(1);
    tftSprite.setCursor(70, 10);

    // test if it is a valid city on cityIndex
    if (cities.size() < cityIndex)
    {
        tftSprite.printf("Invalid City");
        updated = true;
        return false;
    }

    // Basic Infos and Image to display
    JsonVariant city = cities[cityIndex];
    const String cityName = city["name"];
    String status = city["status"];
    const bool clouds = status.indexOf("cloud") >= 0;
    const bool rain = status.indexOf("rain") >= 0;

    tftSprite.print(cityName);
    if (RTC_TimeStruct.Hours > 5 && RTC_TimeStruct.Hours < 13)
    {
        // durante o dia
        if (clouds)
        {
            tftSprite.pushImage(10, 10, 50, 50, weather4);
        }
        else if (rain)
        {
            tftSprite.pushImage(10, 10, 50, 50, weather5);
        }
        else
            tftSprite.pushImage(10, 10, 50, 50, weather1);
    }
    else if (RTC_TimeStruct.Hours < 18)
    {
        // Durante a tarde
        if (clouds)
        {
            tftSprite.pushImage(10, 10, 50, 50, weather4);
        }
        else if (rain)
        {
            tftSprite.pushImage(10, 10, 50, 50, weather5);
        }
        else
            tftSprite.pushImage(10, 10, 50, 50, weather2);
    }
    else
    {
        // Durante a noite
        if (clouds)
        {
            tftSprite.pushImage(10, 10, 50, 50, weather8);
        }
        else if (rain)
        {
            tftSprite.pushImage(10, 10, 50, 50, weather6);
        }
        else
            tftSprite.pushImage(10, 10, 50, 50, weather3);
    }

    // Control info to display
    const float temp = city["temp"];
    const float temp_max = city["temp_max"];
    const float temp_min = city["temp_min"];
    const byte humidity = city["humidity"];
    const unsigned int pressure = city["pressure"];
    const float rain3h = city["rain3h"];
    tftSprite.setCursor(70, 27);

    // Trata os nomes longos
    if (status.equals("overcast clouds"))
        status = "clouds";

    switch (statusInfo)
    {
    case STATUS_INFO_TEMP:
        tftSprite.print(status);
        tftSprite.setCursor(70, 45);
        tftSprite.printf("Temp: %3.1f", temp);
        tftSprite.setCursor(10, 63);
        tftSprite.printf("Min: %3.1f | Max: %3.1f", temp_min, temp_max);
        break;
    case STATUS_INFO_PLUVIOMETRIC:
        tftSprite.printf("Humidity: %d", humidity);
        tftSprite.setCursor(70, 45);
        tftSprite.printf("Atmosf: %d", pressure);
        if (rain3h > 0)
        {
            tftSprite.setCursor(10, 63);
            tftSprite.printf("Chance Rain: %3.2f", rain3h * 100.0);
        }
        break;
    }

    // check info to display
    if (millis() - lastStatusInfo > STATUS_INFO_TIMEOUT)
    {
        statusInfo++;
        if (statusInfo > 1)
            statusInfo = 0;
        lastStatusInfo = millis();
    }

    return true;
}

void WeatherInterface::pressB()
{
    updated = false;
    network.begin();
}
