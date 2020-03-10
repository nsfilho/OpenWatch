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
#ifndef __INTERFACES_H_
#define __INTERFACES_H_
#include "watch_interface.h"
#include <vector>

#define MAX_INTERFACES 10

class Interfaces
{
private:
    std::vector<WatchInterface *> interfaces;
    unsigned long lastUpdate = 0;
public:
    Interfaces();
    void addInterface(WatchInterface *interface);
    WatchInterface *getCurrent();
    WatchInterface *nextInterface();
    void loop();
};

#endif
