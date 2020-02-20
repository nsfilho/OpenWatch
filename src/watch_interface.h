#ifndef __WATCH_H_
#define __WATCH_H_

class WatchInterface
{
public:
    bool displayNetworkStatus;

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
};

#endif