#pragma once

unsigned char rtc_read(unsigned char reg);

int rtc_get_second();
int rtc_get_minute();
int rtc_get_hour();

int rtc_get_day();
int rtc_get_month();
int rtc_get_year();
