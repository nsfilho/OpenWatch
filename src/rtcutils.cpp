#include <M5StickC.h>
#include "rtcutils.h"

RTC_TimeTypeDef RTC_TimeStruct;
RTC_DateTypeDef RTC_DateStruct;

const char *monthName[12] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

void getRTC_info()
{
    M5.Rtc.GetTime(&RTC_TimeStruct);
    M5.Rtc.GetData(&RTC_DateStruct);
}

void setRTC_fromCompiler()
{
    String pt = (__DATE__ " " __TIME__); // PC DATE TIME READ

    //000000000011111111112  Read data position: decade (x10) part
    //012345678901234567890  Read data position: literal (x1) part
    //Jun  6 2019 07:20:41   String format
    char m1[3];
    int m2 = 1; // Month conversion ( Jun to 6 )
    (pt.substring(0, 3)).toCharArray(m1, 4);
    for (int mx = 0; mx < 12; mx++)
    {
        if (strcmp(m1, monthName[mx]) == 0)
        {
            m2 = mx + 1;
            break;
        }
    }

    RTC_DateTypeDef DateStruct; // Month, Date, Year
    DateStruct.Month = m2;
    DateStruct.Date = (pt.substring(4, 6)).toInt();
    DateStruct.Year = (pt.substring(7, 11)).toInt();
    M5.Rtc.SetData(&DateStruct);

    RTC_TimeTypeDef TimeStruct; // Hours, Minutes, Seconds
    TimeStruct.Hours = (pt.substring(12, 14)).toInt();
    TimeStruct.Minutes = (pt.substring(15, 17)).toInt();
    TimeStruct.Seconds = (pt.substring(18, 20)).toInt();
    M5.Rtc.SetTime(&TimeStruct);
}