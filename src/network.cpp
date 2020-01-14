#include <M5StickC.h>
#include <WiFi.h>
#include "main.h"
#include "network.h"

/** Sprite specific for network stack */
TFT_eSprite tftSpriteStatus = TFT_eSprite(&M5.Lcd);

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
bool Network::begin()
{
    tftSprite.setRotation(SCREEN_ROTATION);
    tftSpriteStatus.createSprite(120, 40);
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
void Network::loop()
{
    if (_status == WN_SCANNING && WiFi.scanComplete() >= 0)
        checkKnowsNetwork();
    if (_status != WN_OFF)
        displayStatus();
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
        tftSpriteStatus.fillSprite(BLACK);
        tftSpriteStatus.drawRect(0, 0, 120, 40, WHITE);
        tftSpriteStatus.drawBitmap(5, 5, wifi_logo, 40, 30, WHITE);
        tftSpriteStatus.setTextColor(WHITE);
        tftSpriteStatus.setCursor(50, 5, 1);
        switch (_status)
        {
        case WN_CONNECTING:
            tftSpriteStatus.print("Connecting");
            tftSpriteStatus.setCursor(50, 20);
            tftSpriteStatus.print(WiFi.SSID().c_str());
            break;
        case WN_CONNECTED:
            tftSpriteStatus.print("Connected");
            tftSpriteStatus.setCursor(50, 20);
            tftSpriteStatus.print(WiFi.SSID().c_str());
            break;
        case WN_FAILED:
            tftSpriteStatus.print("Failed");
            break;
        case WN_NO_AVAILABLE:
            tftSpriteStatus.print("No available");
            break;
        case WN_SCANNING:
            tftSpriteStatus.print("Scanning...");
            break;
        case WN_OFF:
            tftSpriteStatus.print("Off");
            break;
        }
        tftSpriteStatus.pushSprite(20, 20);
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
    tftSpriteStatus.deleteSprite();
}