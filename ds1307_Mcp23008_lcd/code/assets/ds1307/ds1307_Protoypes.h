#ifndef  DS1307_PROTOTYPES_H
#define  DS1307_PROTOTYPES_H
//------------------------------------------------------------------------------
#define WRITE_CMD     0xD0
#define READ_CMD      0xD1
//------------------------------------------------------------------------------
void RTC_displayDate(int row, int col, int time[]);
void RTC_displayTime(int row, int col, int time[]);
void RTC_setDateTime(int regAddr, int _data);
void RTC_getDateTime(int time[]);
void RTC_init(void);
void clearString(int str[]);
//------------------------------------------------------------------------------
#endif