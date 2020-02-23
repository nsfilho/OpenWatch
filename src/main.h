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
#ifndef __MAIN_H_
#define __MAIN_H_
#include "config.h"
#include "interfaces/interfaces.h"
#include "ntputils.h"
#include "network.h"

extern Config config;
extern Interfaces interfaces;
extern TFT_eSprite tftSprite;
extern NTPUtils ntpUtils;
extern Network network;

extern unsigned long wakeupTime;

void setup(void);
void initScreen(void);
void loop(void);
bool update_watch_interface(void);
void check_wakeup_timeout(void);

#endif