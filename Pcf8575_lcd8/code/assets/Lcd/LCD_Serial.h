#ifndef LCD_Serial_H
#define LCD_Serial_H
//------------------------------------------------------------------------------
#include "LCD_Serial_Prototypes.h"
#include <./assets/delay/delay.h>
#include <./assets/pcf8575/pcf8575.h>
//------------------------------------------------------------------------------
void LCD_init(char address)
{
  I2C_init();    
  Expander_init(address);
  
  LCD_command(home);
  LCD_command(function_set8);
  LCD_command(display_on);
  LCD_command(clear); 
}
//------------------------------------------------------------------------------
void LCD_data(char _data)
{
  RS = 1;                        //_Data register  ( Strings and characters ).
  LCD_transmit(_data); 
}
//------------------------------------------------------------------------------
void LCD_command(char command)
{
  RS = 0;                        //Instruction register ( commands ).
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
	Expander_write(RS, _data);
	LCD_latch(_data);
}
//------------------------------------------------------------------------------
void LCD_latch(char _data)
{
  char control = 0x00 | RS;
  
	Expander_write((control | EN_high), _data);
	__delay_ms(5);
	Expander_write((control & EN_low), _data);
}
//------------------------------------------------------------------------------
#endif