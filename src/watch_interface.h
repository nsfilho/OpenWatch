#ifndef __WATCH_H_
#define __WATCH_H_

#define POSITION_BAR_TOP 0
#define POSITION_BAR_RIGHT 1
#define POSITION_BAR_BOTTOM 2
#define POSITION_BAR_LEFT 3
#define POSITION_BAR_OFF 4

class WatchInterface
{
public:
    bool displayNetworkStatus;
    bool noSleep;
    byte batteryPos;
    byte screenPos;

    /** 
     * Setup a watch interface
     * Return: if true, push tftSprite to LCD.
    */
    virtual bool setup();

    /**
     * Looping interface
     * Return: if true, push tftSprite to LCD.
     */
    virtual bool loop();
    virtual void finish();
    virtual void pressA();
    virtual void pressB();
    virtual void loopBatteryBar();
    virtual void loopScreenBar();
};

#endif