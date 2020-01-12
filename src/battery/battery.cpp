#include <M5StickC.h>
#include "main.h"
#include "battery.h"

void Battery::setup()
{
    M5.Lcd.setRotation(3);
    M5.Axp.EnableCoulombcounter();
    tftSprite.setRotation(3);
}

void Battery::finish()
{
    M5.Axp.DisableCoulombcounter();
}

void Battery::loop()
{
    tftSprite.fillSprite(BLACK);
    tftSprite.setCursor(0, 0, 1);
    tftSprite.printf("AXP Temp: %.1fC \r\n", M5.Axp.GetTempInAXP192());
    tftSprite.setCursor(0, 10);
    tftSprite.printf("Bat:\r\n  V: %.3fv  I: %.3fma\r\n", M5.Axp.GetBatVoltage(), M5.Axp.GetBatCurrent());
    tftSprite.setCursor(0, 30);
    tftSprite.printf("USB:\r\n  V: %.3fv  I: %.3fma\r\n", M5.Axp.GetVBusVoltage(), M5.Axp.GetVBusCurrent());
    tftSprite.setCursor(0, 50);
    tftSprite.printf("5V-In:\r\n  V: %.3fw  I: %.3fma\r\n", M5.Axp.GetVinVoltage(), M5.Axp.GetVinCurrent());
    tftSprite.setCursor(0, 70);
    tftSprite.printf("Bat power %.3fmw", M5.Axp.GetBatPower());
    tftSprite.pushSprite(0, 0);
}