#ifndef __BUTTON_H_
#define __BUTTON_H_

#define MIN_CLICK 100 // in milliseconds

class DebouncingButton
{

public:
    DebouncingButton(int pin);
    int wasClicked();

private:
    int _pin;

    byte lastState;          // last state
    unsigned long lastCheck; // lastCheck time (millis)
    byte numClicks;          // number of clicks
    byte reset;              // reset in next looping
};

#endif