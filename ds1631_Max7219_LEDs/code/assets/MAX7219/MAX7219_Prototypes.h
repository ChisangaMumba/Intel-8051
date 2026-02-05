#ifndef MAX7219_PROTOTYPES_H
#define	MAX7219_PROTOTYPES_H
//------------------------------------------------------------------------------
#define DECODE_MODE_REG     0x09
#define INTESITY_REG        0x0A
#define SCAN_LIMIT_REG      0x0B
#define SHUTDOWN_REG        0x0C
#define DISPLAY_TEST_REG    0x0F
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
//------------------------------------------------------------------------------
void MAX7219_init(char scanSize);
void MAX7219_write(char reg, signed char _data);
void MAX7219_displayNumber(signed long number);
void MAX7219_displayText(char text[]);
char getDigit(char pos, signed char dp, char asciiChar);
signed char findPosChar(char chars[], char aChar);
char getCustomChar(char asciiChar);
//------------------------------------------------------------------------------
//Common Cathode           0,    1,    2,    3,    4,    5,    6,    7,    8,   9
const char digits[] = { 0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0x7F, 0x73 };
//----------------------------Custom characters---------------------------------
char chars[]    = { '-', ' ', '°', 'C', 'F', '%', 'E', 'O', 'R', '\0'};
char charCode[] = { 0x01, 0x00, 0x63, 0x4E, 0x47, 0x67, 0x4F,0x1D, 0x05, '\0'};
//------------------------------------------------------------------------------
#endif