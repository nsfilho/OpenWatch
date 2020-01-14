#ifndef __NTP_INTERFACE_H_
#define __NTP_INTERFACE_H_
#include "watch_interface.h"

typedef enum
{
    NI_NOT_STARTED = 0,
    NI_UPDATING = 1
} ntpInterface_status_t;

class NtpInterface : public WatchInterface
{
private:
    ntpInterface_status_t _status;

public:
    void setup();
    void loop();
    void pressB();
    void finish();
    void startUpdate();
};

#endif