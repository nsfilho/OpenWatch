#include <M5StickC.h>
#include "main.h"
#include "battery.h"
#include "batteryImgs.h"

bool BatteryInterface::setup()
{
    M5.Axp.EnableCoulombcounter();
    M5.Lcd.setRotation(SCREEN_ROTATION);
    tftSprite.setRotation(SCREEN_ROTATION);
    return false;
}

void BatteryInterface::finish()
{
    M5.Axp.DisableCoulombcounter();
}

bool BatteryInterface::loop()
{
    String tipo = "Battery";
    float voltage, current;
    byte batteryLvl = ((M5.Axp.GetBatVoltage() - MIN_VOLTAGE) / (MAX_VOLTAGE - MIN_VOLTAGE)) * 100;

    tftSprite.fillSprite(WHITE);
    tftSprite.setTextColor(BLACK);
    //tftSprite.setTextSize(1);
    //tftSprite.setCursor(0, 0, 2);
    //tftSprite.printf("AXP Temp: %.1fC \r\n", M5.Axp.GetTempInAXP192());
    if (M5.Axp.GetVBusVoltage() > 4)
    {
        // USB Connected
        tipo = "USB";
        voltage = M5.Axp.GetVBusVoltage();
        current = M5.Axp.GetVBusCurrent();
    }
    else if (M5.Axp.GetVinVoltage() > 3)
    {
        // 5V-In connected
        tipo = "External";
        voltage = M5.Axp.GetVinVoltage();
        current = M5.Axp.GetVinCurrent();
    }
    else
    {
        // Battery
        voltage = M5.Axp.GetBatVoltage();
        current = M5.Axp.GetBatCurrent();
    }
    tftSprite.setCursor(10, 10, 2);
    tftSprite.setTextSize(2);
    tftSprite.print(tipo);
    tftSprite.setTextSize(1);
    tftSprite.setCursor(10, 45);
    tftSprite.printf("V: %.3fv", voltage);
    tftSprite.setCursor(10, 60);
    tftSprite.printf("I: %.3fma\r\n", current);
    //tftSprite.printf("Bat power %.3fmw", M5.Axp.GetBatPower());

    if (batteryLvl > 80)
        tftSprite.pushImage(120, 0, 40, 80, batteryStatus6);
    else if (batteryLvl > 60)
        tftSprite.pushImage(120, 0, 40, 80, batteryStatus5);
    else if (batteryLvl > 40)
        tftSprite.pushImage(120, 0, 40, 80, batteryStatus4);
    else if (batteryLvl > 20)
        tftSprite.pushImage(120, 0, 40, 80, batteryStatus3);
    else if (batteryLvl > 0)
        tftSprite.pushImage(120, 0, 40, 80, batteryStatus2);
    else
        tftSprite.pushImage(120, 0, 40, 80, batteryStatus1);
    return true;
}
