#ifndef __CONFIG_H_
#define __CONFIG_H_

/** Maximum screen brightness */
#define SCREEN_BRIGHTNESS 8

/** Number of seconds without interaction to enter in deepSleep */
#define SCREEN_WAKEUP_TIMEOUT 20 * 1000

/** Delay between update time in watch screen interface */
#define REFRESH_TIME 1000

extern byte screen_brightness;
extern byte watchInterface;

void loadConfig();
void saveConfig();

#endif