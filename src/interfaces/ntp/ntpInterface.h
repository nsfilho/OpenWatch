/**
 * Openwatch Framework
 * Copyright (C) 2020  Nelio Souza Santos Filho <nsfilho@icloud.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>. 
 *
 */
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
    bool started = false;
    String msgToDisplay = "Press B: start";

public:
    NtpInterface();
    bool setup();
    bool loop();
    void pressB(byte count);
    void finish();
    void startUpdate();
};

#endif