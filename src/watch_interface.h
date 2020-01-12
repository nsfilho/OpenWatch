#ifndef __WATCH_H_
#define __WATCH_H_

class WatchInterface
{
public:
    virtual void setup();
    virtual void loop();
    virtual void finish();
    virtual void pressA();
    virtual void pressB();
};

#endif