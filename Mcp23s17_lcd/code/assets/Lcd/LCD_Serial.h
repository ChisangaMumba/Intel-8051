#ifndef LCD_Serial_H
#define LCD_Serial_H
//------------------------------------------------------------------------------
#include "LCD_Serial_Prototypes.h"
#include <./assets/delay/delay.h>
#include <./assets/mcp23s17/mcp23s17.h>
//------------------------------------------------------------------------------
void LCD_init()
{
  EXPANDER_init(0x00,0x00);  //PortA & PortB all outputs
  
  LCD_command(home);
  LCD_command(function_set8);
  LCD_command(display_on);
  LCD_command(clear); 
}
//------------------------------------------------------------------------------
void LCD_data(char _data)
{
  RS = 1;                        //Data register  ( Strings and characters ).
  
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
  EXPANDER_write( OLATA, RS );
  EXPANDER_write( OLATB, _data );
  
  LCD_latch();
}
//------------------------------------------------------------------------------
void LCD_latch()
{
  char _data = 0x00 | RS;
  
  EXPANDER_write( OLATA, (_data | EN_high) );   //Enable is pulsed to latch the data
  __delay_ms(5);
  EXPANDER_write( OLATA, (_data & EN_low) );
}
//------------------------------------------------------------------------------
#endif