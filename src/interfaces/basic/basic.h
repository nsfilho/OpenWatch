#ifndef __BASIC_H_
#define __BASIC_H_

#include "watch_interface.h"

class BasicInterface : public WatchInterface
{
public:
    BasicInterface();
    bool loop();
};

#endif