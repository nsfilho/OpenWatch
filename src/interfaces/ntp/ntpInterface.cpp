#include <M5StickC.h>
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
    messageToDisplay = "Trying connect to Wi-Fi!";
    loop();
    if (network.begin())
    {
        messageToDisplay = "Updating RTC with NTP!";
        loop();
        ntpUtils.begin();
        ntpUtils.update();
        ntpUtils.end();
        messageToDisplay = "RTC updated!";
        loop();
    }
    else
    {
        messageToDisplay = "Failed to connect Wi-Fi!";
    }
    network.end();
}

void NtpInterface::finish()
{
    config.noSleep = false;
    network.end();
}