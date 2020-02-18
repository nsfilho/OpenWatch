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
    if (_status != WN_OFF)
    {
        displayStatus();
        return true;
    }
    return false;
}

void Network::displayStatus()
{
    if (_status == WN_CONNECTING || _status == WN_SCANNING || _lastStatus != _status || millis() - displayStarted < NETWORK_STATUS_DISPLAY)
    {
        if (_lastStatus != _status)
        {
            displayStarted = millis();
            _lastStatus = _status;
        }
        tftSprite.fillRect(20, 20, 120, 40, BLACK);
        tftSprite.drawRect(20, 20, 120, 40, WHITE);
        tftSprite.drawBitmap(25, 25, wifi_logo, 40, 30, WHITE);
        tftSprite.setCursor(70, 25, 1);
        tftSprite.setTextColor(WHITE);
        tftSprite.setTextSize(1);
        switch (_status)
        {
        case WN_CONNECTING:
            tftSprite.print("Connecting");
            tftSprite.setCursor(70, 40);
            tftSprite.print(WiFi.SSID().c_str());
            break;
        case WN_CONNECTED:
            tftSprite.print("Connected");
            tftSprite.setCursor(70, 40);
            tftSprite.print(WiFi.SSID().c_str());
            break;
        case WN_FAILED:
            tftSprite.print("Failed");
            break;
        case WN_NO_AVAILABLE:
            tftSprite.print("No available");
            break;
        case WN_SCANNING:
            tftSprite.print("Scanning...");
            break;
        case WN_OFF:
            tftSprite.print("Off");
            break;
        }
    }
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