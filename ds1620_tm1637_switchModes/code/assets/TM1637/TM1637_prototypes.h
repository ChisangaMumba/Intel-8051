#ifndef TM1637_PROTOTYPES_H
#define	TM1637_PROTOTYPES_H
//------------------------------------------------------------------------------
#include "assets/twoWire/twoWire.h"
//------------------------------------------------------------------------------
#define DISPLAY_MODE  0x40  //Or Keyscan mode 0x42
#define DISPLAY_CTRL  0x87
#define DISPLAY_REG0  0xC0
#define DISPLAY_REG1  0xC1
#define DISPLAY_REG2  0xC2
#define DISPLAY_REG3  0xC3
#define DISPLAY_REG4  0xC4
#define DISPLAY_REG5  0xC5
#define DECIMAL_POINT 0x80
//------------------------------------------------------------------------------
void TM1637_init(char level);
void TM1637_displayNum(long number);
void TM1637_displayText(char text[]);
void TM1637_setBrightness(char brightness);
void TM1637_write(char text[]);
void TM1637_command(char command);
void TM1637_initSend(char command);
void writeChar(char pos, signed char dp, char chr);
char getDigit(char pos, signed char dp, char chr);
char getCustomChar(char chr);
signed char findPosChar(char chars[], char toFind);
//------------------------------------------------------------------------------
//Common Anode             0,    1,    2,    3,    4,    5,    6,    7,    8,   9
code const char digits[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F };
//------------------------------------------------------------------------------
code const char chars[] 		= {  '-',  ' ',  'C',  'F',  '°',  '%', '\0' };
code const char charCode[] = { 0x40, 0x00, 0x39, 0x71, 0x63, 0x73, '\0' };
//------------------------------------------------------------------------------
#endif	/* TM1637_PROTOTYPES_H */