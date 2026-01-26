#ifndef DS3234_RTC_PROTOTYPES_H
#define	DS3234_RTC_PROTOTYPES_H
//------------------------------------------------------------------------------
#define read_cmd                     0x00
#define write_cmd                    0x80
//------------------------------------------------------------------------------
#define control_reg                  0x0E
#define status_reg                   0x0F
//------------------------------------------------------------------------------
void DS3234_init();
int DS3234_read(int addr);
void DS3234_write(int addr,int value);
void DS3234_setTime(int time[]);
void DS3234_getTime(int time[]);
//------------------------------------------------------------------------------
#endif