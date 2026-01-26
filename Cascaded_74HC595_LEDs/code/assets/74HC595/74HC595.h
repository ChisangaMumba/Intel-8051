#ifndef _74HC595_H
#define	_74HC595_H
//------------------------------------------------------------------------------
#include <string.h>
#include "./assets/delay/delay.h"
#include "./assets/soft_spi/Soft_SPI.h"
#include "74HC595_Protoypes.h"
//-------------------------Common Anode-----------------------------------------
                 //   0 , 1  ,  2 ,  3 ,  4 ,  5 ,  6 ,  7 ,  8 ,  9
char digits[10] = { 0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90 }; 
//-------------------------First In First Out Send-------------------------------
void ShiftReg_FIFOSend(char text[])
{
	char pos;
	
  text = get_lastCharAddr(text);
  
  CS1 = 0;
  
  pos = 0;
  while(*text)
  {
    SPI_write( getDigit( pos++, *text--) );
  }
  
  CS1 = 1; 
}
//--------------------------Last In First Out Send-----------------------------
void ShiftReg_LIFOSend(char text[])
{ 
  char pos = 3;
	
  CS1 = 0;
  
  while(*text)
  { 
    SPI_write( getDigit(pos--, *text++) );
  }
  
  CS1 = 1; 
}
//------------------------------------------------------------------------------
char getDigit(char pos,char asciiChar)
{
    char i, digit = 0;
    
    if(asciiChar >= '0' && asciiChar <= '9')
    {
        i = asciiChar - '0';
        digit = (pos == 1) ? (digits[i] & DECIMAL_POINT) : digits[i]; //ANDing with DECIMAL_POINT Turns off MSB
    }
    else
        if(asciiChar == '-')
        {
            digit = (pos == 1) ? (digits[0] & DECIMAL_POINT) : 0xBF;  //0xBF - minus symbol
        }
        else
            if(asciiChar == ' ')
            {
                digit = (pos == 1) ? (digits[0] & DECIMAL_POINT) : 0xFF; //0xFF - blank. used for leading zero suppression
            }
    
    return digit;
}
//------------------------------------------------------------------------------
char* get_lastCharAddr(char text[])
{
  char lastAddr =  strlen(text) - 1;  
  
  return text + lastAddr;
}
//------------------------------------------------------------------------------
#endif	