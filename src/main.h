#ifndef __MAIN_H_
#define __MAIN_H_
#include "config.h"
#include "interfaces/interfaces.h"

extern Config config;
extern Interfaces interfaces;
extern TFT_eSprite tftSprite;
extern unsigned long wakeupTime;

void setup(void);
void loop(void);
void update_watch_interface(void);
void check_wakeup_timeout(void);

#endif