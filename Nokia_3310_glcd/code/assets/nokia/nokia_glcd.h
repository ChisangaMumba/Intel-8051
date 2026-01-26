#ifndef NOKIA_3310_GLCD_C
#define NOKIA_3310_GLCD_C
//------------------------------------------------------------------------------
sbit DC  = P1^6;
sbit RST = P1^7;
//------------------------------------------------------------------------------
#include "nokia_glcd_prototypes.h"
//------------------------------------------------------------------------------
void LCD_init()
{
	SPI_init();
  
	LCD_reset();
  LCD_command(EXTENDED_COMMANDS);
  LCD_command(CONTRAST);
  LCD_command(TEMP_COEFFIECIENT);
  LCD_command(BIAS_MODE); 
	LCD_command(BASIC_COMMANDS);
  LCD_command(ALL_SEGS_ON);
	
	LCD_fill(FILL);
	LCD_fill(CLEAR);
}
//------------------------------------------------------------------------------
void LCD_address(unsigned char row, unsigned char col)
{	
	LCD_command(ROW0 | row);
  LCD_command(COL0 | (col * 6)); 
}
//------------------------------------------------------------------------------
void LCD_command(unsigned char command)
{
	CS1 = 0;
	
  DC = 0;                        //Instruction Register ( commands ). Data/Command pin, D/C=1 - Data, D/C = 0 - Command
  SPI_write(command); 
	
	CS1 = 1;
}
//------------------------------------------------------------------------------
void LCD_string(unsigned char row, unsigned char col, char * text)
{
  LCD_address(row, col);  
  
	CS1 = 0;
	
	DC = 1;												//Data Register  ( Strings and characters ). Data/Command pin, D/C=1 - Data, D/C = 0 - Command
  while(*text)
  {
		writeChar(*text++);
		SPI_write(SPACE);
  }
	
	CS1 = 1;
}
//------------------------------------------------------------------------------
void writeChar(unsigned char chr)
{
	unsigned char col;
	
	for(col = 0; col < 5; col++)
	{
		if(chr >= 32 && chr <= 127)						//Standard ascii Printable chars range 32 - 127 or 0 - 95 (after subtraction). degree symbol num ° is 144 after subtraction
			SPI_write(chars[chr - ' '][col]);		//(' ' = 32) chr - 32...because the first 32  ASCII character codes are none Printable (control chars)
		else
			SPI_write(customChars[0][col]); 		//Custom Char is ° symbol
	}
}
//------------------------------------------------------------------------------
void LCD_image(const unsigned char *image)
{
	int i;
	
	CS1 = 0;															
	
	DC = 1;																		//Data Register ( Strings and characters ). Data/Command pin, D/C=1 - Data, D/C = 0 - Command
	for(i = 0; i < 504; i++)
		SPI_write(image[i]);
	
	CS1 = 1; 
}
//------------------------------------------------------------------------------
void LCD_fill(unsigned char data_)
{
	int i;
	
	CS1 = 0;															
	
	DC = 1;																	  //Data Register ( Strings and characters ). Data/Command pin, D/C=1 - Data, D/C = 0 - Command
	for(i = 0; i < 504; i++)
		SPI_write(data_);
	
	CS1 = 1; 
}
//------------------------------------------------------------------------------
void LCD_reset()
{
	RST = 0;
	__delay_ms(100);
	RST = 1;
}
//------------------------------------------------------------------------------
#endif