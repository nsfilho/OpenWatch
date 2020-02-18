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
    watch_network_status_t _lastStatus;
    watch_network_status_t _status;
    unsigned long displayStarted;
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

// 'wifi', 40x30px
const unsigned char wifi_logo[] PROGMEM = {
    0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x07, 0xff, 0xe0, 0x00, 0x00, 0x0f, 0xff, 0xf0, 0x00, 0x00,
    0x3f, 0xff, 0xfc, 0x00, 0x00, 0x3f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff,
    0xff, 0xff, 0xf0, 0x1f, 0xff, 0xff, 0x00, 0x08, 0x3f, 0xff, 0xfe, 0x00, 0x04, 0x7f, 0xff, 0xfc,
    0x00, 0x02, 0xf7, 0xb9, 0x38, 0xfe, 0xc1, 0xf3, 0x39, 0x38, 0xfe, 0xc1, 0xf3, 0x19, 0xf8, 0xc0,
    0x01, 0xf3, 0x1b, 0x38, 0xc0, 0xc1, 0xfa, 0x53, 0x38, 0xfc, 0xc1, 0xf8, 0x43, 0x38, 0xfc, 0xc1,
    0xf8, 0xc7, 0x38, 0xc0, 0xc1, 0xf8, 0xc7, 0x38, 0xc0, 0xc1, 0xfc, 0xe7, 0x38, 0xc0, 0xc1, 0xfd,
    0xff, 0xb0, 0x00, 0x01, 0x7f, 0xff, 0xf0, 0x00, 0x02, 0x3f, 0xff, 0xe0, 0x00, 0x04, 0x1f, 0xff,
    0xc0, 0x00, 0x08, 0x07, 0xff, 0x9f, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff,
    0xfc, 0x00, 0x00, 0x3f, 0xff, 0xfc, 0x00, 0x00, 0x0f, 0xff, 0xf0, 0x00, 0x00, 0x03, 0xff, 0xc0,
    0x00, 0x00, 0x00, 0xff, 0x00, 0x00};

#endif