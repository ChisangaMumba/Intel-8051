#ifndef LCD_Serial_H
#define LCD_Serial_H
//------------------------------------------------------------------------------
#include <./assets/delay/delay.h>
#include "LCD_Serial_Prototypes.h"
#include <./assets/74HC595/74HC595.h>
//------------------------------------------------------------------------------
void LCD_init(void)
{
	SR_init();
  
  LCD_command(home);
  LCD_command(function_set4);
  LCD_command(display_on);
  LCD_command(clear); 
}
//------------------------------------------------------------------------------
void LCD_data(char data_)
{
  RS = 1;                        //Data register_  ( Strings and characters ).
  
  LCD_transmit(data_); 
}
//------------------------------------------------------------------------------
void LCD_command(char command)
{
  RS = 0;                        //Instruction register_ ( commands ).
  
  LCD_transmit(command); 
}
//------------------------------------------------------------------------------
void LCD_string(char row, char col, char *text)
{
  LCD_command(RowAddr[row] + col);  
  
  while(*text)
  {
		char chr = *text++;
		
		if(chr == '°')
			chr = DEG_SYMBOL;
		
		if(chr != 194)				//° is implicitly split into 194 and 176 by the arduino c++ compiler
			LCD_data(chr);
  }
}
//------------------------------------------------------------------------------
void LCD_transmit(char data_)
{
	LCD_sendNibble(data_ & 0xF0);     //Higher Nibble
  LCD_sendNibble(data_ << 4);       //Lower Nibble
}
//------------------------------------------------------------------------------
void LCD_sendNibble(char data_)
{
  data_ = data_ | RS;
	
  //Enable is pulsed to latch the data
  SR_send(data_ | EN_high);
  __delay_ms(5);
  SR_send(data_ & EN_low);
}
//------------------------------------------------------------------------------
#endif