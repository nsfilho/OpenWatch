#ifndef __NTP_UTILS_H_
#define __NTP_UTILS_H_

class NTPUtils
{
private:
    bool active;
    char *server;

public:
    NTPUtils();
    void begin();
    void update();
    void loop();
    void force();
    void end();
};

#endif