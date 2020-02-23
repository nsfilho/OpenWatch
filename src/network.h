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