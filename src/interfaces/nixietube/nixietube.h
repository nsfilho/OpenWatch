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
#ifndef __NIXIETUBE_H_
#define __NIXIETUBE_H_
#include "watch_interface.h"

class NixieTube1 : public WatchInterface
{
public:
    bool setup();
    bool loop();
};

class NixieTube2 : public WatchInterface
{
public:
    bool setup();
    bool loop();
};

class NixieTube3 : public WatchInterface
{
public:
    bool setup();
    bool loop();
};

bool nixietube_setup();

#endif