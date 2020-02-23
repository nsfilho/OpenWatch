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
#include <WiFi.h>
#include "main.h"
#include "network.h"

/**
 * Instantiate network class
 */
Network::Network()
{
    _status = WN_OFF;
}

/**
 * Scan all available networks and try to connect
 */
void Network::begin()
{
    _status = WN_SCANNING;
    WiFi.scanNetworks(true, false, false, 500);
}

/**
 * Return network status
 */
watch_network_status_t Network::status()
{
    return _status;
}

/**
 * Async routines
 */
bool Network::loop()
{
    if (_status == WN_SCANNING && WiFi.scanComplete() >= 0)
        checkKnowsNetwork();
    return false;
}

/**
 * After scan ends, try to connected to any knows network
 */
void Network::checkKnowsNetwork()
{
    _status = WN_CONNECTING;
    const int totalNetworks = WiFi.scanComplete();
    for (int x = 0; x < totalNetworks && !WiFi.isConnected(); x++)
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
            while (!WiFi.isConnected() && millis() - tryingConnect < config.network_connection_timeout)
                delay(NETWORK_CONNECTION_DELAY);
            if (!WiFi.isConnected())
                _status = WN_FAILED;
        }
    }
    if (WiFi.isConnected())
        _status = WN_CONNECTED;
    else if (_status == WN_CONNECTING)
        _status = WN_NO_AVAILABLE;
    WiFi.scanDelete();
}

/**
 * Return if is connected to Wi-Fi Network
 */
bool Network::isConnect()
{
    return WiFi.isConnected();
}

/**
 * Shutdown Wi-Fi interface
 */
void Network::end()
{
    _status = WN_OFF;
    WiFi.disconnect(true);
}