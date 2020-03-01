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
#include <WiFi.h>
#include "main.h"
#include "watch_interface.h"
#include "watch_interface_imgs.h"

bool WatchInterface::setup()
{
    return setup(BLACK);
}

bool WatchInterface::setup(uint32_t color)
{
    M5.Lcd.setRotation(SCREEN_ROTATION);
    tftSprite.setRotation(SCREEN_ROTATION);
    tftSprite.fillScreen(color);
    return false;
}

/**
 * Return true if your code buffer all display info in Sprite.
 */
bool WatchInterface::loop()
{
    // do nothing
    return false;
}

bool WatchInterface::loopStatus()
{
    bool updateSprite = loop();
    updateSprite = loopBatteryBar() || updateSprite;
    updateSprite = loopScreenBar() || updateSprite;
    updateSprite = loopNetwork() || updateSprite;
    return updateSprite;
}

void WatchInterface::finish()
{
    // Save energy
    if (network.status() != WN_OFF)
        network.end();
}

void WatchInterface::pressA()
{
    config.nextWatchInterface();
}

void WatchInterface::pressB()
{
    // normally used to start config menu (for watch interface)
    config.nextScreenBrightness();
}

bool WatchInterface::loopBatteryBar()
{
    switch (batteryPos)
    {
    case POSITION_BAR_TOP:
        tftSprite.fillRect(0, 1, BATTERY_BAR_WIDTH(160), 4, GREEN);
        break;
    case POSITION_BAR_BOTTOM:
        tftSprite.fillRect(0, 77, BATTERY_BAR_WIDTH(160), 80, GREEN);
        break;
    case POSITION_BAR_LEFT:
        tftSprite.fillRect(0, 0, 3, BATTERY_BAR_WIDTH(80), GREEN);
        break;
    case POSITION_BAR_RIGHT:
        tftSprite.fillRect(77, 0, 80, BATTERY_BAR_WIDTH(80), GREEN);
        break;
    default:
        return false;
    }
    return true;
}

bool WatchInterface::loopScreenBar()
{
    switch (screenPos)
    {
    case POSITION_BAR_TOP:
        tftSprite.fillRect(0, 1, 160 - SCREEN_BAR_WIDTH(160), 4, RED);
        break;
    case POSITION_BAR_BOTTOM:
        tftSprite.fillRect(0, 77, 160 - SCREEN_BAR_WIDTH(160), 80, RED);
        break;
    case POSITION_BAR_LEFT:
        tftSprite.fillRect(0, 0, 3, SCREEN_BAR_WIDTH(80), RED);
        break;
    case POSITION_BAR_RIGHT:
        tftSprite.fillRect(77, 0, 80, SCREEN_BAR_WIDTH(80), RED);
        break;
    default:
        return false;
    }
    return true;
}

bool WatchInterface::loopNetwork()
{
    switch (networkStatus)
    {
    case NETWORK_STATUS_NONE:
        return false;
        break;
    case NETWORK_STATUS_SMALL_TOP_RIGHT:
    case NETWORK_STATUS_SMALL_TOP_LEFT:
    case NETWORK_STATUS_SMALL_BOTTOM_RIGHT:
    case NETWORK_STATUS_SMALL_BOTTOM_LEFT:
        return loopNetworkSmall();
        break;
    case NETWORK_STATUS_DIALOG:
        return loopNetworkDialog();
        break;
    }
    return false;
}

bool WatchInterface::loopNetworkDialog()
{
    const watch_network_status_t status = network.status();
    if (status == WN_OFF)
        return false;
    if (status == WN_CONNECTING || status == WN_SCANNING || status != lastNetworkStatus ||
        millis() - lastNetworkStatusTime < NETWORK_STATUS_DIALOG_TIMEOUT)
    {
        tftSprite.fillRect(18, 20, 122, 40, BLACK);
        tftSprite.drawRect(18, 20, 122, 40, WHITE);
        tftSprite.drawBitmap(23, 25, wifi_logo, 40, 30, WHITE);
        tftSprite.setCursor(68, 25, 1);
        tftSprite.setTextColor(WHITE);
        tftSprite.setTextSize(1);
        switch (status)
        {
        case WN_CONNECTING:
            tftSprite.print("Connecting");
            tftSprite.setCursor(68, 40);
            tftSprite.print(WiFi.SSID().c_str());
            break;
        case WN_CONNECTED:
            tftSprite.print("Connected");
            tftSprite.setCursor(68, 40);
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
        if (status != lastNetworkStatus)
        {
            lastNetworkStatus = status;
            lastNetworkStatusTime = millis();
        }
        return true;
    }
    return false;
}

bool WatchInterface::loopNetworkSmall()
{
    const watch_network_status_t status = network.status();
    if (status == WN_OFF)
        return false;
    switch (networkStatus) {
        case NETWORK_STATUS_SMALL_TOP_RIGHT:
            tftSprite.pushImage(134, 1, 25, 12, wifiSmall);
            break;
        default:
            break;
    }
    return true;
}
