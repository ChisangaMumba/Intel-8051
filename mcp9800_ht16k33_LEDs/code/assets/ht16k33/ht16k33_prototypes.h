#ifndef HT16K33_PROTOTYPES_H
#define	HT16K33_PROTOTYPES_H
//------------------------------------------------------------------------------
#define HT16K33_ADDRESS  0xE0      //Address bits can be altered on device if wished
#define OSCILLATOR_ON    0x21      //HT16K33 internal oscillator
#define DIGITAL_DIM      0xE0      
#define DISPLAY_SETUP    0x81
#define DISPLAY_MEMORY   0x00      //Start address. auto increments on every write. valid from 0x00 - 0xFF then auto wraps after last valid address
#define DECIMAL_POINT    0x80
//------------------------------------------------------------------------------
void ht16k33_init(void);
void ht16k33_on(void);
void ht16k33_blink(char _data);
void ht16k33_setBrightness(unsigned char _data);
void ht16k33_displayNum(signed long num);
void ht16k33_displayNumText(char text[]);
void ht16k33_write(char text[]);
void ht16k33_char(char asciiChar, signed char dp, char pos);
char getDigit(char pos, signed char dp, char asciiChar);
signed char findPosChar(char chars[], char aChar);
char getCustomChar(char asciiChar);
//------------------------------------------------------------------------------
//Common Cathode           0,    1,    2,    3,    4,    5,    6,    7,    8,   9
const char digits[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F };
//----------------------------Custom characters---------------------------------
char chars[]    = { '-', ' ', '°', 'C', 'F', '%', 'E', 'O', 'R', '\0'};
char charCode[] = { 0x40, 0x00, 0x63, 0x39, 0x71, 0x73, 0x79,0x3F, 0x50, '\0'};
//------------------------------------------------------------------------------
#endif	/* HT16K33_PROTOTYPES_H */