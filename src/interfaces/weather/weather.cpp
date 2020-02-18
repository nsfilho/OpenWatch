#include "main.h"
#include "weather.h"

bool WeatherInterface::setup()
{
    tftSprite.fillSprite(BLACK);
    tftSprite.pushImage(10, 10, 50, 50, weather_partial);
    return true;
}