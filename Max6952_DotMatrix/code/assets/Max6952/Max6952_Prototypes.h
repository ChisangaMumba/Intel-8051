#ifndef MAX6952_PROTOTYPES_H
#define	MAX6952_PROTOTYPES_H
//------------------------------------------------------------------------------
#define DECODE_MODE_REG     0x01
#define INTESITY_REG10      0x01
#define INTESITY_REG32      0x02
#define SCAN_LIMIT_REG      0x03
#define SHUTDOWN_REG        0x04
#define DISPLAY_TEST_REG    0x07
//------------------------------------------------------------------------------
#define DISABLE_DECODE      0x00
#define DECODE_ALL          0xFF
#define BRIGHTNESS          0xFF
#define SCAN_LOW_NIBBLE     0x03
#define SCAN_ALL_DIGITS     0x07   
#define SHUTDOWN_MODE       0x00
#define NORMAL_OPERATION    0x01
#define DISABLE_TEST_MODE   0x00
#define ENABLE_TEST_MODE    0x01
#define DECIMAL_POINT       0x80
#define DISPLAY_REG0        0x20
//------------------------------------------------------------------------------
void MAX6952_init();
void MAX6952_write(char reg, signed char data_);
void MAX6952_displayNumber(signed int number);
void MAX6952_displayText(char text[]);
char getCustomChar(char asciiChar);
//------------------------------------------------------------------------------
char customChar[] = "£¥€°µ±";             //see Max6952 datasheet page 13 (Table 14. Character Map)
char charCode[] = {24,25,26,27,28,29}; 
//------------------------------------------------------------------------------
#endif