#include "main.h"
#include "ntpInterface.h"
#include "icons.h"

String msgDisplay1;
bool started = false;

NtpInterface::NtpInterface()
{
    screenPos = POSITION_BAR_BOTTOM;
}

bool NtpInterface::setup()
{
    WatchInterface::setup();
    msgDisplay1 = "Press B: Start";
    started = false;
    return false;
}

bool NtpInterface::loop()
{
    WatchInterface::loop();
    tftSprite.fillSprite(BLACK);
    tftSprite.fillRect(0, 0, 160, 23, ORANGE);
    tftSprite.drawBitmap(1, 1, icon_gears, 20, 20, WHITE);
    tftSprite.setTextColor(WHITE, ORANGE);
    tftSprite.setTextSize(1);
    tftSprite.setCursor(30, 4, 2);
    tftSprite.printf("NTP > RTC");
    tftSprite.setTextColor(WHITE, BLACK);
    tftSprite.setCursor(5, 32);
    tftSprite.printf(msgDisplay1.c_str());
    // Check if connection is ready to start update
    if (started && network.isConnect())
        startUpdate();
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
    wakeupTime = millis();
    noSleep = false;
    started = false;
}

void NtpInterface::pressB()
{
    started = true;
    noSleep = true;
    network.begin();
}

void NtpInterface::finish()
{
    noSleep = false;
    network.end();
}