#include <M5StickC.h>
#include "nixietube.h"
#include "vfd_18x34.c"
#include "vfd_35x67.c"

const uint8_t *n[] = { // vfd font 18x34
    vfd_18x34_0, vfd_18x34_1, vfd_18x34_2, vfd_18x34_3, vfd_18x34_4,
    vfd_18x34_5, vfd_18x34_6, vfd_18x34_7, vfd_18x34_8, vfd_18x34_9};
const uint8_t *m[] = { // vfd font 35x67
    vfd_35x67_0, vfd_35x67_1, vfd_35x67_2, vfd_35x67_3, vfd_35x67_4,
    vfd_35x67_5, vfd_35x67_6, vfd_35x67_7, vfd_35x67_8, vfd_35x67_9};

void nixietube_setup()
{
    M5.Lcd.setRotation(3);
}

void nixietube_2_line()
{
    M5.Rtc.GetTime(&RTC_TimeStruct);
    M5.Rtc.GetData(&RTC_DateStruct);
    int h1 = int(RTC_TimeStruct.Hours / 10);
    int h2 = int(RTC_TimeStruct.Hours - h1 * 10);
    int i1 = int(RTC_TimeStruct.Minutes / 10);
    int i2 = int(RTC_TimeStruct.Minutes - i1 * 10);
    int s1 = int(RTC_TimeStruct.Seconds / 10);
    int s2 = int(RTC_TimeStruct.Seconds - s1 * 10);
    M5.Lcd.pushImage(2, 0, 35, 67, (uint16_t *)m[h1]);
    M5.Lcd.pushImage(41, 0, 35, 67, (uint16_t *)m[h2]);
    M5.Lcd.drawPixel(79, 22, ORANGE);
    M5.Lcd.drawPixel(79, 48, ORANGE);
    M5.Lcd.drawPixel(79, 21, YELLOW);
    M5.Lcd.drawPixel(79, 47, YELLOW);
    M5.Lcd.pushImage(83, 0, 35, 67, (uint16_t *)m[i1]);
    M5.Lcd.pushImage(121, 0, 35, 67, (uint16_t *)m[i2]);
    M5.Lcd.pushImage(120, 45, 18, 34, (uint16_t *)n[s1]);
    M5.Lcd.pushImage(140, 45, 18, 34, (uint16_t *)n[s2]);
}

void nixietube_1_line()
{
    M5.Rtc.GetTime(&RTC_TimeStruct);
    M5.Rtc.GetData(&RTC_DateStruct);
    //Serial.printf("Data: %04d-%02d-%02d\n",RTC_DateStruct.Year,RTC_DateStruct.Month,RTC_DateStruct.Date);
    //Serial.printf("Week: %d\n",RTC_DateStruct.WeekDay);
    //Serial.printf("Time: %02d : %02d : %02d\n",RTC_TimeStruct.Hours,RTC_TimeStruct.Minutes,RTC_TimeStruct.Seconds);
    // Data: 2019-06-06
    // Week: 0
    // Time: 09 : 55 : 26
    int y1 = int(RTC_DateStruct.Year / 1000);
    int y2 = int((RTC_DateStruct.Year - y1 * 1000) / 100);
    int y3 = int((RTC_DateStruct.Year - y1 * 1000 - y2 * 100) / 10);
    int y4 = int(RTC_DateStruct.Year - y1 * 1000 - y2 * 100 - y3 * 10);
    int j1 = int(RTC_DateStruct.Month / 10);
    int j2 = int(RTC_DateStruct.Month - j1 * 10);
    int d1 = int(RTC_DateStruct.Date / 10);
    int d2 = int(RTC_DateStruct.Date - d1 * 10);
    int h1 = int(RTC_TimeStruct.Hours / 10);
    int h2 = int(RTC_TimeStruct.Hours - h1 * 10);
    int i1 = int(RTC_TimeStruct.Minutes / 10);
    int i2 = int(RTC_TimeStruct.Minutes - i1 * 10);
    int s1 = int(RTC_TimeStruct.Seconds / 10);
    int s2 = int(RTC_TimeStruct.Seconds - s1 * 10);

    M5.Lcd.pushImage(0, 0, 18, 34, (uint16_t *)n[y1]);
    M5.Lcd.pushImage(19, 0, 18, 34, (uint16_t *)n[y2]);
    M5.Lcd.pushImage(38, 0, 18, 34, (uint16_t *)n[y3]);
    M5.Lcd.pushImage(57, 0, 18, 34, (uint16_t *)n[y4]);
    M5.Lcd.drawPixel(77, 13, ORANGE);
    M5.Lcd.drawPixel(77, 23, ORANGE);
    M5.Lcd.pushImage(80, 0, 18, 34, (uint16_t *)n[j1]);
    M5.Lcd.pushImage(99, 0, 18, 34, (uint16_t *)n[j2]);
    M5.Lcd.drawPixel(118, 13, ORANGE);
    M5.Lcd.drawPixel(119, 23, ORANGE);
    M5.Lcd.pushImage(120, 0, 18, 34, (uint16_t *)n[d1]);
    M5.Lcd.pushImage(140, 0, 18, 34, (uint16_t *)n[d2]);

    M5.Lcd.pushImage(00, 40, 18, 34, (uint16_t *)n[h1]);
    M5.Lcd.pushImage(20, 40, 18, 34, (uint16_t *)n[h2]);
    M5.Lcd.drawPixel(48, 54, ORANGE);
    M5.Lcd.drawPixel(48, 64, ORANGE);
    M5.Lcd.pushImage(60, 40, 18, 34, (uint16_t *)n[i1]);
    M5.Lcd.pushImage(80, 40, 18, 34, (uint16_t *)n[i2]);
    M5.Lcd.drawPixel(108, 54, ORANGE);
    M5.Lcd.drawPixel(108, 64, ORANGE);
    M5.Lcd.pushImage(120, 40, 18, 34, (uint16_t *)n[s1]);
    M5.Lcd.pushImage(140, 40, 18, 34, (uint16_t *)n[s2]);
}

void nixietube_3_line()
{
    M5.Rtc.GetTime(&RTC_TimeStruct);
    M5.Rtc.GetData(&RTC_DateStruct);
    int i1 = int(RTC_TimeStruct.Minutes / 10);
    int i2 = int(RTC_TimeStruct.Minutes - i1 * 10);
    int s1 = int(RTC_TimeStruct.Seconds / 10);
    int s2 = int(RTC_TimeStruct.Seconds - s1 * 10);

    M5.Lcd.pushImage(2, 6, 35, 67, (uint16_t *)m[i1]);
    M5.Lcd.pushImage(41, 6, 35, 67, (uint16_t *)m[i2]);
    M5.Lcd.drawPixel(79, 28, ORANGE);
    M5.Lcd.drawPixel(79, 54, ORANGE);
    M5.Lcd.drawPixel(79, 27, YELLOW);
    M5.Lcd.drawPixel(79, 53, YELLOW);
    M5.Lcd.pushImage(83, 6, 35, 67, (uint16_t *)m[s1]);
    M5.Lcd.pushImage(121, 6, 35, 67, (uint16_t *)m[s2]);
}
