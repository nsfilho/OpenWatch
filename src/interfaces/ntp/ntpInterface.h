#ifndef __NTP_INTERFACE_H_
#define __NTP_INTERFACE_H_
#include "watch_interface.h"

class NtpInterface : public WatchInterface
{
public:
    void setup();
    void loop();
    void pressB();
    void finish();
};

#endif