#include <M5StickC.h>
#include "main.h"
#include "ntpInterface.h"
#include "interfaces/icons.h"

String msgDisplay1;
String msgDisplay2;
bool started;

void NtpInterface::setup()
{
    started = false;
    config.noSleep = true;
    M5.Lcd.setRotation(SCREEN_ROTATION);
    tftSprite.setRotation(SCREEN_ROTATION);
    msgDisplay1 = "Press B:";
    msgDisplay2 = "Start";
}

void NtpInterface::loop()
{
    // Frame border
    tftSprite.fillSprite(BLACK);
    tftSprite.fillRect(0, 0, 160, 23, ORANGE);
    tftSprite.drawBitmap(1, 1, icon_gears, 20, 20, WHITE);
    tftSprite.setTextColor(WHITE, ORANGE);
    tftSprite.setTextSize(2);
    tftSprite.setCursor(30, 4, 1);
    tftSprite.printf("NTP > RTC");

    // Content
    tftSprite.setTextColor(WHITE, BLACK);
    tftSprite.setCursor(5, 32, 1);
    tftSprite.printf(msgDisplay1.c_str());
    tftSprite.setCursor(5, 52, 1);
    tftSprite.printf(msgDisplay2.c_str());

    // Render
    tftSprite.pushSprite(0, 0);

    // Check if connection is ready to start update
    if (started && network.isConnect())
    {
        started = false;
        startUpdate();
    }
}

void NtpInterface::startUpdate()
{
    msgDisplay2 = "";
    msgDisplay1 = "Updating...";
    loop();
    ntpUtils.begin();
    ntpUtils.update();
    ntpUtils.end();
    msgDisplay1 = "Updated!";
    loop();
    network.end();
}

void NtpInterface::pressB()
{
    started = true;
    network.begin();
}

void NtpInterface::finish()
{
    config.noSleep = false;
    network.end();
}