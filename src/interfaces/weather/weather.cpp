#include <HTTPClient.h>
#include "main.h"
#include "weather.h"
#include "weatherImgs.h"
#include "rtcutils.h"

bool updated = false;

bool WeatherInterface::setup()
{
    WatchInterface::setup();
    displayNetworkStatus = false;
    tftSprite.fillSprite(BLACK);
    if (needUpdate())
        network.begin();
    return false;
}

bool WeatherInterface::needUpdate()
{
    byte index = config.jsonConfig["openWeather"]["index"];
    JsonVariant city = config.jsonConfig["openWeather"]["cities"][index];
    const long lastRead = city["lastRead"];
    return getRTC_EllapsedTime(&RTC_DateStruct, &RTC_TimeStruct) - lastRead > 3600;
}

bool WeatherInterface::loop()
{
    byte index = config.jsonConfig["openWeather"]["index"];
    JsonArray cities = config.jsonConfig["openWeather"]["cities"];
    // tftSprite.setFreeFont(&FreeMono9pt7b);
    tftSprite.setTextFont(2);
    tftSprite.setTextSize(1);
    tftSprite.setCursor(70, 10);
    if (cities.size() < index)
    {
        // the city on index does not exists more.
        tftSprite.printf("Invalid City");
        updated = true;
        return false;
    }

    JsonVariant city = cities[index];
    if (!updated && network.isConnect())
    {
        String appId = config.jsonConfig["openWeather"]["appid"];
        String units = config.jsonConfig["openWeather"]["units"];
        String cityName = city["name"];
        HTTPClient http;
        String url = "http://api.openweathermap.org/data/2.5/weather?q=" + cityName + "&appid=" + appId + "&units=" + units;
        http.begin(url);
        const int httpCode = http.GET();
        if (httpCode == 200)
        {
            StaticJsonDocument<512> weatherInfo;
            deserializeJson(weatherInfo, http.getString());
            city["temp"] = weatherInfo["main"]["temp"];
            city["temp_min"] = weatherInfo["main"]["temp_min"];
            city["temp_max"] = weatherInfo["main"]["temp_max"];
            city["pressure"] = weatherInfo["main"]["pressure"];
            city["humidity"] = weatherInfo["main"]["humidity"];
            city["status"] = weatherInfo["weather"][0]["description"];
            city["lastRead"] = getRTC_EllapsedTime(&RTC_DateStruct, &RTC_TimeStruct);
            Serial.println("Updated weather info");
            config.save();
        }
        http.end();
        network.end();
        updated = true;
    }
    const String cityName = city["name"];
    const String status = city["status"];
    const float temp = city["temp_min"];
    const float temp_max = city["temp_max"];
    const float temp_min = city["temp_min"];
    // tftSprite.setFreeFont(&FreeMonoBold9pt7b);
    tftSprite.print(cityName);
    // tftSprite.setFreeFont(&FreeMono9pt7b);
    // tftSprite.setTextSize(1);
    tftSprite.setCursor(70, 25);
    tftSprite.print(status);
    tftSprite.setCursor(70, 45);
    tftSprite.printf("Temp: %3.1f", temp);
    tftSprite.setCursor(10, 63);
    tftSprite.printf("Min: %3.1f | Max: %3.1f", temp_min, temp_max);
    tftSprite.pushImage(10, 10, 50, 50, weather_partial);
    return true;
}

void WeatherInterface::finish()
{
    network.end();
}