#ifndef MAX6950_PROTOTYPES_H
#define	MAX6950_PROTOTYPES_H
//------------------------------------------------------------------------------
#include <string.h>
#include <stdio.h>
#include <ctype.h>
//------------------------------------------------------------------------------
#define DECODE_MODE_REG     0x01
#define INTESITY_REG        0x02
#define SCAN_LIMIT_REG      0x03
#define SHUTDOWN_REG        0x04
#define DISPLAY_TEST_REG    0x07
//------------------------------------------------------------------------------
#define DISABLE_DECODE      0x00
#define DECODE_ALL          0xFF
#define BRIGHTNESS          0x0F
#define SCAN_LOW_NIBBLE     0x03
#define SCAN_ALL_DIGITS     0x07   
#define SHUTDOWN_MODE       0x00
#define NORMAL_OPERATION    0x01
#define DISABLE_TEST_MODE   0x00
#define ENABLE_TEST_MODE    0x01
#define DECIMAL_POINT       0x80
#define DISPLAY_REG0        0x20
//------------------------------------------------------------------------------
void MAX6950_init();
void MAX6950_write(char reg,signed char data_);
void MAX6950_displayNumber(float number);
void MAX6950_displayText(char text[]);
char getDigit(char pos, signed char dp, char asciiChar);
signed char findPosChar(char chars[], char aChar);
char getCustomChar(char asciiChar);
//------------------------------------------------------------------------------
//Common Cathode           0,    1,    2,    3,    4,    5,    6,    7,    8,   9
code char digits[] = { 0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0x7F, 0x73 };
//----------------------------Custom characters---------------------------------
code char chars[]    = {  '-',  ' ',  '°',  'C',  'F',  '%',  'E', 'O',  'R', '\0' };
code char charCode[] = { 0x01, 0x00, 0x63, 0x4E, 0x47, 0x67, 0x4F,0x1D, 0x05, '\0' };
//------------------------------------------------------------------------------
#endif