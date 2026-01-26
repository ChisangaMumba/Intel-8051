#ifndef LCD4_H
#define	LCD4_H
//------------------------------------------------------------------------------
#include <lcd4_prototypes.h>
#include <lcd4_pins.h>
//------------------------------------------------------------------------------
void __delay(int n)
{
	int i, j;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < 100; j++)
		{}
	}
}
//-----------------------Follow Datasheet instructions--------------------------
void LCD_init()
{
  LCD_command(home);
  LCD_command(function_set4);   
  LCD_command(display_on);      
  LCD_command(auto_increment);
}
//------------------------------------------------------------------------------
void LCD_command(char command)
{
  RS = 0;                     //Instruction register ( commands ).
  LCD_transmit(command);
}
//------------------------------------------------------------------------------
void LCD_data(char _data)
{
  RS = 1;                     //Data register  ( strings and characters ).
  LCD_transmit(_data);
}
//------------------------------------------------------------------------------
void LCD_string(char row, char column, char text[])
{
  LCD_command(rowAddr[row] + column);  //Set coordinates.
  while(*text)
  {
    LCD_data(*text++);
  }
}
//------------------------------------------------------------------------------
void LCD_transmit(char _data)
{
  char pinBits[8];
   
  LCD_getBits(pinBits, _data);
  LCD_sendBits(pinBits);
}
//------------------------------------------------------------------------------
void LCD_sendBits(char pinBit[])
{
  //Higher Nibble
  D4 = pinBit[4];
  D5 = pinBit[5];
  D6 = pinBit[6];
  D7 = pinBit[7];
  latch();
  
  //Lower Nibble
  D4 = pinBit[0];
  D5 = pinBit[1];
  D6 = pinBit[2];
  D7 = pinBit[3];
  latch();
}
//------------------------------------------------------------------------------
void LCD_getBits(char pinBit[], char _data)
{ 
	char i;
  for(i = 0; i < 8; i++)
  {
    pinBit[i] = ((_data >> i) & 0x01) ? 1 : 0;
  }
}
//------------------------------------------------------------------------------
void latch()
{
  EN  = 1;
  __delay(5);
  EN  = 0;
}
//------------------------------------------------------------------------------
#endif