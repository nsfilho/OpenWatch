#ifndef __WATCH_INTERFACE_H_
#define __WATCH_INTERFACE_H_

#include <M5StickC.h>
#include "config.h"
#include "network.h"

#define SCREEN_BAR_WIDTH(X) (((millis() - wakeupTime) * X) / config.screen_wakeup_timeout)
#define BATTERY_BAR_WIDTH(X) (((M5.Axp.GetBatVoltage() - MIN_VOLTAGE) * X) / (MAX_VOLTAGE - MIN_VOLTAGE))
#define BATTERY_LVL ((M5.Axp.GetBatVoltage() - MIN_VOLTAGE) / (MAX_VOLTAGE - MIN_VOLTAGE)) * 100

#define POSITION_BAR_TOP 0
#define POSITION_BAR_RIGHT 1
#define POSITION_BAR_BOTTOM 2
#define POSITION_BAR_LEFT 3
#define POSITION_BAR_OFF 4

#define NETWORK_STATUS_NONE 0
#define NETWORK_STATUS_SMALL 1
#define NETWORK_STATUS_DIALOG 2
#define NETWORK_STATUS_DIALOG_TIMEOUT 3000

class WatchInterface
{
private:
    watch_network_status_t lastNetworkStatus = WN_OFF;
    unsigned long lastNetworkStatusTime = 0;
    bool loopNetworkSmall();
    bool loopNetworkDialog();
    bool loopBatteryBar();
    bool loopScreenBar();
    bool loopNetwork();

protected:
    byte batteryPos = POSITION_BAR_OFF;
    byte screenPos = POSITION_BAR_OFF;
    byte networkStatus = NETWORK_STATUS_DIALOG;
    virtual bool loop();

public:
    bool noSleep = false;

    /** 
     * Setup a watch interface
     * Return: if true, push tftSprite to LCD.
    */
    virtual bool setup(uint32_t color);
    virtual bool setup();

    /**
     * Looping interface
     * Return: if true, push tftSprite to LCD.
     */
    virtual bool loopStatus();
    virtual void finish();
    virtual void pressA();
    virtual void pressB();
};

#endif
