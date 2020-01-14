#ifndef __CONFIG_H_
#define __CONFIG_H_
#include <M5StickC.h>

/** Screen default rotation */
#define SCREEN_ROTATION 3

/** Maximum screen brightness */
#define SCREEN_BRIGHTNESS 8

/** Number of seconds without interaction to enter in deepSleep */
#define SCREEN_WAKEUP_TIMEOUT 20 * 1000

/** Delay between update time in watch screen interface */
#define REFRESH_TIME 1000

/** Definitions for Battery Measure */
#define MAX_VOLTAGE 4.1
#define MIN_VOLTAGE 3.7

/** Network definitions */
#define NETWORK_CONNECTION_TIMEOUT 5000
#define NETWORK_CONNECTION_DELAY 100
#define NETWORK_STATUS_DISPLAY 2000

class Config
{
private:
    byte _config_changed;

public:
    byte screen_brightness;
    byte screen_watchInterface;
    bool noSleep;
    unsigned int network_connection_timeout;
    unsigned int screen_refreshTime;
    unsigned long screen_wakeup_timeout;
    Config();
    void begin();
    void setScreenBrightness(byte value);
    void setWatchInterface(byte value);
    void nextWatchInterface(void);
    void nextScreenBrightness(void);
    void save(void);
    void load(void);
    int existsNetwork(String name);
    String getNetworkPassword(String name);
    String getNTPServer();
    int getNTPOffset();
};

#endif