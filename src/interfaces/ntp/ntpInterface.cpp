#include <M5StickC.h>
#include "main.h"
#include "ntpInterface.h"
#include "interfaces/icons.h"

String msgDisplay1;
bool started;

bool NtpInterface::setup()
{
    WatchInterface::setup();
    started = false;
    config.noSleep = true;
    msgDisplay1 = "Press B: Start";
    return false;
}

bool NtpInterface::loop()
{
    // Frame border
    tftSprite.fillSprite(BLACK);
    tftSprite.fillRect(0, 0, 160, 23, ORANGE);
    tftSprite.drawBitmap(1, 1, icon_gears, 20, 20, WHITE);
    tftSprite.setTextColor(WHITE, ORANGE);
    tftSprite.setTextSize(1);
    tftSprite.setCursor(30, 4, 2);
    tftSprite.printf("NTP > RTC");

    // Content
    tftSprite.setTextColor(WHITE, BLACK);
    tftSprite.setCursor(5, 32);
    tftSprite.printf(msgDisplay1.c_str());

    // Check if connection is ready to start update
    if (started && network.isConnect())
    {
        started = false;
        startUpdate();
    }
    return true;
}

void NtpInterface::startUpdate()
{
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