#include <M5StickC.h>
#include "config.h"
#include "main.h"
#include "button.h"
#include "rtcutils.h"
#include "nixietube/nixietube.h"

RTC_TimeTypeDef RTC_TimeStruct;
RTC_DateTypeDef RTC_DateStruct;

byte watchInterface = 0;       // Which watch interface to render
unsigned long wakeupTime = 0;  // Contains wake up (from sleep) millis
unsigned long lastRefresh = 0; // Control last watchInterface refresh
DebouncingButton button = DebouncingButton(M5_BUTTON_HOME);

void setup(void)
{
    M5.begin();
    M5.Lcd.fillScreen(BLACK);
    M5.Axp.ScreenBreath(SCREEN_BRIGHTNESS); // 7-15
    lastRefresh = millis();
    // setRTC_fromCompiler();
    wakeupTime = millis();
}

void loop(void)
{
    // Ações do botão
    if (button.wasClicked() > 0)
    {
        watchInterface = (watchInterface == 3 ? 1 : watchInterface + 1);
        M5.Lcd.fillScreen(BLACK);
    }

    update_watch_interface();
    check_wakeup_timeout();
}

/**
 * Start a routine to update the watch screen interface (time)
 */
void update_watch_interface(void)
{
    if (millis() - lastRefresh > REFRESH_TIME)
    {
        switch (watchInterface)
        {
        case 1:
            nixietube_1_line();
            break;
        case 2:
            nixietube_2_line();
            break;
        case 3:
            nixietube_3_line();
            break;
        }
        lastRefresh = millis();
    }
}

void check_wakeup_timeout(void)
{
}
