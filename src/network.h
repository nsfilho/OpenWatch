#ifndef __NETWORK_H_
#define __NETWORK_H_

class Network
{
public:
    Network();
    bool begin();
    bool isConnect();
    void loop();
    void end();
};

#endif