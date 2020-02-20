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

void setRTC_fromNTP(String value)
{
    // 00000000001111111111
    // 01234567890123456789
    // 2020-01-12T21:16:15Z
    RTC_DateTypeDef DateStruct; // Month, Date, Year
    DateStruct.Year = (value.substring(0, 4)).toInt();
    DateStruct.Month = (value.substring(5, 7)).toInt();
    DateStruct.Date = (value.substring(8, 10)).toInt();
    M5.Rtc.SetData(&DateStruct);

    RTC_TimeTypeDef TimeStruct; // Hours, Minutes, Seconds
    TimeStruct.Hours = (value.substring(11, 13)).toInt();
    TimeStruct.Minutes = (value.substring(14, 16)).toInt();
    TimeStruct.Seconds = (value.substring(17, 19)).toInt();
    M5.Rtc.SetTime(&TimeStruct);
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

byte months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// count from year 2010
long getRTC_EllapsedTime(RTC_DateTypeDef *date, RTC_TimeTypeDef *time)
{
    return time->Seconds +
           time->Minutes * 60 +
           time->Hours * 3600 +
           date->Date * 86400 +
           months[date->Month] * 86400 +
           (date->Year - 2010) * 365 * 86400;
}