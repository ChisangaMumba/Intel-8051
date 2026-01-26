#ifndef NOKIA_3310_GLCD_H
#define NOKIA_3310_GLCD_H      
//------------------------------------------------------------------------------
#include <./assets/delay/delay.h>
#include <./assets/Soft_SPI/Soft_SPI.h>
#include "image.h"
#include "ascii_chars.h"
//------------------------------------------------------------------------------
#define EXTENDED_COMMANDS   0x21		//use extended instruction set      
#define CONTRAST     				0xC8		//set LCD Vop for contrast
#define TEMP_COEFFIECIENT   0x06		//set temperature coefficient
#define BIAS_MODE    				0x13		//select Bias voltage 
#define BASIC_COMMANDS      0x20		//use basic instruction se
#define ALL_SEGS_ON         0x0C		//set normal mode
//------------------------------------------------------------------------------
#define ROW0								0x40
#define COL0								0x80
//------------------------------------------------------------------------------
#define FILL								0xFF
#define CLEAR								0x00
#define SPACE								CLEAR
//------------------------------------------------------------------------------
void LCD_init(void);
void LCD_address(unsigned char row, unsigned char col);
void LCD_command(unsigned char command);
void LCD_string(unsigned char row, unsigned char col, char * text);
void LCD_image(const unsigned char *image);
void LCD_reset(void);
void writeChar(unsigned char chr);
void LCD_fill(unsigned char data_);
//------------------------------------------------------------------------------
#endif