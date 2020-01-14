#include <M5StickC.h>
#include "main.h"
#include "battery.h"
#include "batteryImgs.h"

void BatteryInterface::setup()
{
    M5.Axp.EnableCoulombcounter();
    M5.Lcd.setRotation(SCREEN_ROTATION);
    tftSprite.setRotation(SCREEN_ROTATION);
}

void BatteryInterface::finish()
{
    M5.Axp.DisableCoulombcounter();
}

void BatteryInterface::loop()
{
    byte batteryLvl = ((M5.Axp.GetBatVoltage() - MIN_VOLTAGE) / (MAX_VOLTAGE - MIN_VOLTAGE)) * 100;
    tftSprite.fillSprite(WHITE);
    if (batteryLvl > 80)
        tftSprite.drawBitmap(0, 0, batteryStatus1, 160, 80, BLACK);
    else if (batteryLvl > 60)
        tftSprite.drawBitmap(0, 0, batteryStatus2, 160, 80, BLACK);
    else if (batteryLvl > 40)
        tftSprite.drawBitmap(0, 0, batteryStatus3, 160, 80, BLACK);
    else if (batteryLvl > 20)
        tftSprite.drawBitmap(0, 0, batteryStatus4, 160, 80, BLACK);
    else if (batteryLvl > 0)
        tftSprite.drawBitmap(0, 0, batteryStatus5, 160, 80, BLACK);
    else
        tftSprite.drawBitmap(0, 0, batteryStatus6, 160, 80, BLACK);
    tftSprite.pushSprite(0, 0);
}

//tftSprite.pushImage(0,0,160,80, battery100);
// tftSprite.setCursor(0, 0, 1);
// tftSprite.printf("AXP Temp: %.1fC \r\n", M5.Axp.GetTempInAXP192());
// tftSprite.setCursor(0, 10);
// tftSprite.printf("Bat:\r\n  V: %.3fv  I: %.3fma\r\n", M5.Axp.GetBatVoltage(), M5.Axp.GetBatCurrent());
// tftSprite.setCursor(0, 30);
// tftSprite.printf("USB:\r\n  V: %.3fv  I: %.3fma\r\n", M5.Axp.GetVBusVoltage(), M5.Axp.GetVBusCurrent());
// tftSprite.setCursor(0, 50);
// tftSprite.printf("5V-In:\r\n  V: %.3fw  I: %.3fma\r\n", M5.Axp.GetVinVoltage(), M5.Axp.GetVinCurrent());
// tftSprite.setCursor(0, 70);
// tftSprite.printf("Bat power %.3fmw", M5.Axp.GetBatPower());