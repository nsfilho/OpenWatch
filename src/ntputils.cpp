#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include "main.h"
#include "ntputils.h"
#include "rtcutils.h"

WiFiUDP ntpUDP;

NTPUtils::NTPUtils()
{
    active = false;
}

void NTPUtils::begin()
{
    active = true;
}

void NTPUtils::update()
{
    server = strdup(config.getNTPServer().c_str());
    NTPClient client = NTPClient(ntpUDP, server, config.getNTPOffset());
    if (client.forceUpdate())
    {
        Serial.print("NTP result: ");
        Serial.println(client.getFormattedDate());
        setRTC_fromNTP(client.getFormattedDate());
    }
    free(server);
}

void NTPUtils::force()
{
}

void NTPUtils::loop()
{
}

void NTPUtils::end()
{
    active = false;
}