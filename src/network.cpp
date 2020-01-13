#include <WiFi.h>
#include "main.h"
#include "network.h"

Network::Network()
{
}

bool Network::begin()
{
    byte totalNetworks = WiFi.scanNetworks(false, false, false, 500);
    for (byte x = 0; x < totalNetworks && !WiFi.isConnected(); x++)
    {
        String network_name = WiFi.SSID(x);
#ifdef DEBUG_WATCH
        Serial.print("SSID: ");
        Serial.print(WiFi.SSID(x));
        Serial.print(" - RSSI: ");
        Serial.print(WiFi.RSSI(x));
        Serial.println("");
#endif
        int network_index = config.existsNetwork(network_name);
        if (network_index >= 0)
        {
            WiFi.begin(network_name.c_str(), config.getNetworkPassword(network_name).c_str());
            unsigned long tryingConnect = millis();
            while (!WiFi.isConnected() && millis() - tryingConnect < 5000)
                delay(100);
        }
    }
    return WiFi.isConnected();
}

void Network::loop()
{
}

bool Network::isConnect()
{
    return WiFi.isConnected();
}

void Network::end()
{
    WiFi.disconnect(true);
}