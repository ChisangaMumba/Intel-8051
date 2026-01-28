#ifndef MAX7219_H
#define	MAX7219_H
//------------------------Dot Matrix LED  Driver--------------------------------
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "../Soft_SPI/Soft_SPI.h"
#include "MAX7219_Prototypes.h"
//------------------------------------------------------------------------------
void MAX7219_init(char scanSize)
{
  SPI_init();
     
	MAX7219_write(DECODE_MODE_REG, DISABLE_DECODE);    
  MAX7219_write(INTESITY_REG, BRIGHTNESS);     
  MAX7219_write(SCAN_LIMIT_REG, scanSize);     
  MAX7219_write(SHUTDOWN_REG, NORMAL_OPERATION);
}
//------------------------------------------------------------------------------
void MAX7219_write(char reg, signed char _data)
{
  CS1 = 0; 
  
  SPI_write(reg); 
  SPI_write(_data); 
  
  CS1 = 1;
}
//------------------------------------------------------------------------------
void MAX7219_displayNumber(signed long number)
{   
	char strNum[10]; 
  sprintf(strNum,"%6li",number);
	
	MAX7219_displayText(strNum);
}
//------------------------------------------------------------------------------
void MAX7219_displayText(char text[])
{ 
	char pos;
	
  for(pos = 0; pos < strlen(text); pos++)
  {   
    char i = text[pos];  
    MAX7219_write( pos+1, getDigit(i) );
  }
}
//------------------------------------------------------------------------------
char getDigit(char asciiChar)
{
	char digit = 0;
	
	if(asciiChar >= '0' && asciiChar <= '9') 
	{
		unsigned char i = asciiChar - '0';
		digit = digits[i];
	}
	else
			{
				digit = getCustomChar(asciiChar);
			}
		
	return digit;
}
//------------------------------------------------------------------------------
char getCustomChar(char asciiChar)
{
	char i, digit = 0x00;
		
  for(i = 0; i < 9; i++)
  {
		 if(toupper(asciiChar) == chars[i])
		 {
		   digit = charCode[i];
			 break;
		 }
	}	
					
	return digit;			
}
//------------------------------------------------------------------------------
#endif	