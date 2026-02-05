#ifndef SAA1064_PROTOTYPES_H
#define	SAA1064_PROTOTYPES_H
//------------------------------------------------------------------------------
#include <string.h>
#include <ctype.h>
#include "../../assets/i2c/I2C.h"
//------------------------------------------------------------------------------
#define SAA1064_ADDRESS  0x70      //Address bits can be altered on device if wished
#define CONTROL_REG      0x00      
#define DISPLAY_REG      0x01      
#define DEVICE_CONFIG    0x47      //adds 12 mA to segment output current. dynamic mode 
#define DECIMAL_POINT    0x80
//------------------------------------------------------------------------------
void SAA1064_init(void);
void SAA1064_on(void);
void SAA1064_blink(char data_);
void SAA1064_setBrightness(unsigned char data_);
void SAA1064_displayInt(signed int num);
void SAA1064_displayFloat(float number);
void SAA1064_displayText(char text[]);
void SAA1064_write(char text[]);
void writeChar(char chrPos, signed char dpPos, char chr);
char getCustomChar(char chr);
char getDigit(char charPos, signed char dpPos, char chr);
signed char findPosChar(char chars[], char toFind);
char* get_lastCharAddr(char text[]);
//------------------------------------------------------------------------------
//Common Cathode           0,    1,    2,    3,    4,    5,    6,    7,    8,   9
code char digits[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F };
//----------------------------Custom characters---------------------------------
code char chars[]    = { '-', ' ', '°', 'C', 'F', '%', 'E', 'O', 'R', '\0'};
code char charCode[] = { 0x40, 0x00, 0x63, 0x4E, 0x47, 0x67, 0x4F,0x1D, 0x05, '\0'};
//------------------------------------------------------------------------------
#endif	/* SAA1064_PROTOTYPES_H */