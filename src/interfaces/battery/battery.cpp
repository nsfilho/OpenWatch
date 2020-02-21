#include <M5StickC.h>
#include "main.h"
#include "battery.h"
#include "batteryImgs.h"

bool BatteryInterface::setup()
{
    WatchInterface::setup();
    screenPos = POSITION_BAR_LEFT;
    M5.Axp.EnableCoulombcounter();
    return false;
}

void BatteryInterface::finish()
{
    M5.Axp.DisableCoulombcounter();
}

bool BatteryInterface::loop()
{
    tftSprite.fillSprite(WHITE);
    WatchInterface::loop();

    float voltage, current;
    String tipo = "Battery";
    byte batteryLvl = ((M5.Axp.GetBatVoltage() - MIN_VOLTAGE) / (MAX_VOLTAGE - MIN_VOLTAGE)) * 100;
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
    tftSprite.setTextColor(BLACK);
    tftSprite.setCursor(13, 10, 2);
    tftSprite.setTextSize(2);
    tftSprite.print(tipo);
    tftSprite.setTextSize(1);
    tftSprite.setCursor(13, 45);
    tftSprite.printf("V: %.3fv", voltage);
    tftSprite.setCursor(13, 60);
    tftSprite.printf("I: %.3fma\r\n", current);
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
