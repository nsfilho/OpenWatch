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
#include "main.h"
#include "web.h"
#include "../icons.h"

WebInterface::WebInterface()
{
    virtualMouse = MOUSE_WEIGHT;
    noSleep = true;
}

bool WebInterface::setup()
{
    WatchInterface::setup();
    msgToDisplay = "Press B: To Count";
    networkStatus = NETWORK_STATUS_DIALOG;
    return false;
}

bool WebInterface::loop()
{
    WatchInterface::loop();
    frameTemplate("Web > Cfg", msgToDisplay, icon_gears);
    return true;
}

void WebInterface::pressB(byte count)
{
    // started = true;
    // network.begin();
    msgToDisplay = "Total: " + String(count);
}