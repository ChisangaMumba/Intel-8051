#ifndef MAX6953_PROTOTYPES_H
#define	MAX6953_PROTOTYPES_H
//------------------------------------------------------------------------------
#define DECODE_MODE_REG     0x01
#define INTESITY_REG10      0x01
#define INTESITY_REG32      0x02
#define SCAN_LIMIT_REG      0x03
#define SHUTDOWN_REG        0x04
#define DISPLAY_TEST_REG    0x07
#define DEVICE_ADDRESS0     0xA0
#define DEVICE_ADDRESS1     0xA1
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
void MAX6953_init();
void MAX6953_write(char reg, signed char data_);
void MAX6953_displayNumber(signed int number);
void MAX6953_displayText(char text[]);
char getCustomChar(char asciiChar);
//------------------------------------------------------------------------------
char customChar[] = "£¥€°µ±";             //see Max6953 datasheet page 13 (Table 14. Character Map)
char charCode[] = {24,25,26,27,28,29}; 
//------------------------------------------------------------------------------
#endif