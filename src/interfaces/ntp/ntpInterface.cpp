#include <M5StickC.h>
#include <WiFi.h>
#include "main.h"
#include "ntpInterface.h"

String messageToDisplay;

void NtpInterface::setup()
{
    M5.Lcd.setRotation(3);
    tftSprite.setRotation(3);
    config.noSleep = true;
    messageToDisplay = "Press B: Start";
}

void NtpInterface::loop()
{
    tftSprite.fillSprite(BLACK);
    tftSprite.setCursor(5, 2, 1);
    tftSprite.setTextColor(WHITE, ORANGE);
    tftSprite.fillRect(0, 0, 160, 12, ORANGE);
    tftSprite.printf("Config: NTP Interface");

    // Content
    tftSprite.setTextColor(WHITE, BLACK);
    tftSprite.setCursor(5, 22, 1);
    tftSprite.printf(messageToDisplay.c_str());

    // Render
    tftSprite.pushSprite(0, 0);
}

void NtpInterface::pressB()
{
    messageToDisplay = "Scanning Wi-Fi...";
    loop();
    byte totalNetworks = WiFi.scanNetworks(false, false, false, 500);
    for (byte x = 0; x < totalNetworks; x++)
    {
        String network_name = WiFi.SSID(x);
        Serial.print("SSID: ");
        Serial.print(WiFi.SSID(x));
        Serial.print(" - RSSI: ");
        Serial.print(WiFi.RSSI(x));
        Serial.println("");

        int network_index = config.existsNetwork(network_name);
        if (network_index >= 0)
        {
            messageToDisplay = "Connecting to: " + network_name;
            loop();

            WiFi.begin(network_name.c_str(), config.getNetworkPassword(network_name).c_str());
            unsigned long tryingConnect = millis();
            while (!WiFi.isConnected() && millis() - tryingConnect < 5000)
            {
                messageToDisplay = "Connecting to: " + network_name + "\n(" + String(millis() - tryingConnect) + ")";
                loop();
                delay(100);
            }
        }
        else
        {
        }
        Serial.println("");
    }

    if (WiFi.isConnected())
    {
        messageToDisplay = "Updating RTC with NTP...";
    }
    else
    {
        messageToDisplay = "Failed to find valid Wi-Fi...";
    }
}

void NtpInterface::finish()
{
    config.noSleep = false;
    WiFi.disconnect(true);
}