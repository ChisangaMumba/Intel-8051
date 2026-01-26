#ifndef PCF2123_PROTOTYPES_H
#define	PCF2123_PROTOTYPES_H
//------------------------------------------------------------------------------
void PCF2123_init();
void PCF2123_Write(int time[]);
void PCF2123_Read(int time[]);
//------------------------------------------------------------------------------
#define SA        0x01   //subaddress; other codes will cause the device to ignore data transfer
#define RD        0x90   //RD + Subaddress + Sec
#define WR        0x10
//------------------------------------------------------------------------------
#define OS_FLAG   0x7F
#define SEC_REG   0x02
#define MIN_REG   0x03
#define HOUR_REG  0x04
#define DAY_REG   0x05
#define MDAY_REG  0x06
#define WDAY_REG  0x07
#define MONTH_REG 0x08
#define YEAR_REG  0x09
//------------------------------------------------------------------------------
#endif