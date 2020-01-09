#ifndef __RTCUTILS_H_
#define __RTCUTILS_H_
#include <M5StickC.h>

extern RTC_TimeTypeDef RTC_TimeStruct;
extern RTC_DateTypeDef RTC_DateStruct;
extern const char *monthName[12];

void getRTC_info();
void setRTC_fromCompiler();

#endif