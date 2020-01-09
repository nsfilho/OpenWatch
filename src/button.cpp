/**
 * Button debouncing class
 * 
 */
#include <M5StickC.h>
#include "button.h"

DebouncingButton::DebouncingButton(int pin)
{
    _pin = pin;
    lastState = HIGH;
    lastCheck = millis();
    numClicks = 0;
    pinMode(pin, INPUT);
}

int DebouncingButton::wasClicked() 
{
    byte state = digitalRead(_pin);
    if (reset) {
        numClicks = 0;
        reset = 0;
    } 
    if (state != lastState && state == LOW) {   // Está clicando
        lastState = state;
        lastCheck = millis();
    } else if (state != lastState && (millis() - lastCheck > MIN_CLICK)) {
        lastCheck = millis();
        lastState = state;
        numClicks++;
        reset++;
    }
    return numClicks;
}