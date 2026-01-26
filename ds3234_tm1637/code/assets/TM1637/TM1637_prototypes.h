#ifndef TM1637_PROTOTYPES_H
#define	TM1637_PROTOTYPES_H
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
void TM1637_displayNum(signed int number);
void TM1637_displayNumText(char text[]);
void TM1637_setBrightness(char brightness);
void TM1637_write(char text[]);
void TM1637_command(char command);
void TM1637_initSend(char command);
char getDigit(char pos,char asciiChar);
char* toString(signed int number);
//------------------------------------------------------------------------------
#endif	/* TM1637_PROTOTYPES_H */