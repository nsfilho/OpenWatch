#ifndef __NETWORK_H_
#define __NETWORK_H_

typedef enum
{
    WN_OFF = 0,
    WN_SCANNING = 1,
    WN_CONNECTING = 2,
    WN_CONNECTED = 3,
    WN_NO_AVAILABLE = 4,
    WN_FAILED = 5
} watch_network_status_t;

class Network
{
private:
    watch_network_status_t _status;
    void checkKnowsNetwork();
    void displayStatus();

public:
    Network();
    void begin();
    bool isConnect();
    bool loop();
    void end();
    watch_network_status_t status();
};

#endif