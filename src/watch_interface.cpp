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
    tftSprite.fillSprite(color);
    if (virtualMouse)
    {
        M5.Mpu6886.Init();
    }
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
    if (virtualMouse)
    {
        tftSprite.fillCircle((int)mouseX, (int)mouseY, 5, GREEN);
        updateSprite = true;
    }
    return updateSprite;
}

void WatchInterface::finish()
{
    // Save energy
    if (network.status() != WN_OFF)
        network.end();
}

void WatchInterface::pressA(byte count)
{
    config.nextWatchInterface();
}

void WatchInterface::pressB(byte count)
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
    switch (networkStatus)
    {
    case NETWORK_STATUS_SMALL_TOP_RIGHT:
        tftSprite.pushImage(134, 1, 25, 12, wifiSmall);
        break;
    default:
        break;
    }
    return true;
}

void WatchInterface::frameTemplate(String title, String msgDisplay, const uint8_t *icon)
{
    tftSprite.fillSprite(BLACK);
    tftSprite.fillRect(0, 0, 160, 23, ORANGE);
    tftSprite.drawBitmap(1, 1, icon, 20, 20, WHITE);
    tftSprite.setTextColor(WHITE, ORANGE);
    tftSprite.setTextSize(1);
    tftSprite.setCursor(30, 4, 2);
    tftSprite.printf(title.c_str());
    tftSprite.setTextColor(WHITE, BLACK);
    tftSprite.setCursor(5, 32);
    tftSprite.printf(msgDisplay.c_str());
}

float mapFloat(float value, float fromMin, float fromMax, float toMin, float toMax)
{
    return (value / (fromMax - fromMin)) * (toMax - toMin);
}

void WatchInterface::update()
{
    if (virtualMouse != MOUSE_OFF)
    {
        int16_t ax, ay, az;
        //int16_t gx, gy, gz;
        M5.Mpu6886.getAccelAdc(&ax, &ay, &az);
        //M5.Mpu6886.getGyroAdc(&gx, &gy, &gz);
        if (SCREEN_ROTATION == 3 && virtualMouse == MOUSE_DIRECT_MAP)
        {
            mouseY = map(ax * -1, IMU_MAX_ROTATION_MAP_X_MIN, IMU_MAX_ROTATION_MAP_X_MAX, 5, 75);
            mouseX = map(ay * -1, IMU_MAX_ROTATION_MAP_Y_MIN, IMU_MAX_ROTATION_MAP_Y_MAX, 5, 155);
            //Serial.printf("%d,%d\n", mouseX, mouseY);
        }
        else if (SCREEN_ROTATION == 3 && virtualMouse == MOUSE_WEIGHT)
        {
            mouseY += mapFloat(ax * -1, IMU_MAX_ROTATION_WEIGHT_X_MIN, IMU_MAX_ROTATION_WEIGHT_X_MAX, IMU_MAX_ROTATION_WEIGHT_X * -1, IMU_MAX_ROTATION_WEIGHT_X);
            mouseX += mapFloat(ay * -1, IMU_MAX_ROTATION_WEIGHT_Y_MIN, IMU_MAX_ROTATION_WEIGHT_Y_MAX, IMU_MAX_ROTATION_WEIGHT_Y * -1, IMU_MAX_ROTATION_WEIGHT_Y);
            if (mouseY < 5)
                mouseY = 5;
            if (mouseY > 75)
                mouseY = 75;
            if (mouseX < 5)
                mouseX = 5;
            if (mouseX > 155)
                mouseX = 155;
        }
    }
}