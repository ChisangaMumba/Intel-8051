#ifndef HT16K33_PROTOTYPES_H
#define	HT16K33_PROTOTYPES_H
#include <./assets/characters/ascii.h>
//------------------------------------------------------------------------------
#define HT16K33_ADDRESS  0xE0      //Address bits can be altered on device if wished
#define OSCILLATOR_ON    0x21      //HT16K33 internal oscillator
#define DIGITAL_DIM      0xE0      
#define DISPLAY_SETUP    0x81
#define DISPLAY_MEMORY   0x00      //Start address. auto increments on every write. valid from 0x00 - 0xFF then auto wraps after last valid address
//------------------------------------------------------------------------------
void ht16k33_init(void);
void ht16k33_on(void);
void ht16k33_blink(char _data);
void ht16k33_setBrightness(unsigned char _data);
void ht16k33_displayNum(signed long int number);
void ht16k33_displayText(char text[]);
void ht16k33_write(char text[]);
void ht16k33_char(char pos, signed char dp, char _data);
signed char findPosChar(char chars[], char toFind);
//------------------------------------------------------------------------------
#endif	/* HT16K33_PROTOTYPES_H */