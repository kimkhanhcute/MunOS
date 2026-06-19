#include "rtc.h"
#include "io.h"

static int bcd_to_int(unsigned char bcd)
{
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

unsigned char rtc_read(unsigned char reg)
{
    outb(0x70, reg);
    return inb(0x71);
}

int rtc_get_second()
{
    return bcd_to_int(rtc_read(0x00));
}

int rtc_get_minute()
{
    return bcd_to_int(rtc_read(0x02));
}

int rtc_get_hour()
{
    return bcd_to_int(rtc_read(0x04));
}

int rtc_get_day()
{
    return bcd_to_int(rtc_read(0x07));
}

int rtc_get_month()
{
    return bcd_to_int(rtc_read(0x08));
}

int rtc_get_year()
{
    return 2000 + bcd_to_int(rtc_read(0x09));
}
