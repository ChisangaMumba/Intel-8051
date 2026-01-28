#ifndef LCD_Serial_H
#define LCD_Serial_H
//------------------------------------------------------------------------------
#include "LCD_Serial_Prototypes.h"
#include <./assets/delay/delay.h>
#include <./assets/pcf8574/pcf8574.h>
//------------------------------------------------------------------------------
void LCD_init(char address)
{
  I2C_init();    
  Expander_init(address);
  
  LCD_command(home);
  LCD_command(function_set4);
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
void LCD_transmit(char _data)
{
  LCD_sendNibble(_data & 0xF0);     //Higher Nibble
  LCD_sendNibble(_data << 4);       //Lower Nibble
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
void LCD_sendNibble(char _data)
{
  _data = _data | RS;
	
  //Enable is pulsed to latch the _data
  Expander_write(_data | EN_high);
  __delay_ms(5);
  Expander_write(_data & EN_low);
}
//------------------------------------------------------------------------------
#endif