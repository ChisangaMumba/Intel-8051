#ifndef LCD_Serial_H
#define LCD_Serial_H
//------------------------------------------------------------------------------
#include <./assets/delay/delay.h>
#include "LCD_Serial_Prototypes.h"
#include <./assets/74HC595/74HC595.h>
//------------------------------------------------------------------------------
void LCD_init()
{
	SR_init();
  
  LCD_command(home);
  LCD_command(function_set8);
  LCD_command(display_on);
  LCD_command(clear); 
}
//------------------------------------------------------------------------------
void LCD_data(char _data)
{
  RS = 1;                        //Data register_  ( Strings and characters ).
  
  LCD_transmit(_data); 
}
//------------------------------------------------------------------------------
void LCD_command(char command)
{
  RS = 0;                        //Instruction register_ ( commands ).
  
  LCD_transmit(command); 
}
//------------------------------------------------------------------------------
void LCD_string(char row, char col, char * text)
{
  LCD_command(RowAddr[row] + col);  
  
  while(*text)
  {
    LCD_data(*text++);
  }
}
//------------------------------------------------------------------------------
void LCD_transmit(char _data)
{
	SR_control(RS);
	SR_data(_data);
  
  LCD_latch();
}
//------------------------------------------------------------------------------
void LCD_latch()
{
  char _data = 0x00 | RS;
	
	SR_control(_data | EN_high);
	__delay_ms(5);
	SR_control(_data & EN_low);
}
//------------------------------------------------------------------------------
#endif