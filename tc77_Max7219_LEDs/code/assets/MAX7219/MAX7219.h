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
	char pos = 0, i, dp;  //dp: decimal point
	
	dp = findPosChar(text, '.');
	
  for(i = 0; i < strlen(text); i++)
  {   
    char asciiChar = text[i];  
		
		if(asciiChar != '.')
		{
			MAX7219_write( pos+1, getDigit(pos, dp, asciiChar) );
			pos++;
		}
  }
}
//------------------------------------------------------------------------------
char getDigit(char pos, signed char dp, char asciiChar)
{
	char digit = 0;
	
	digit = (asciiChar >= '0' && asciiChar <= '9') ? digits[asciiChar - '0'] : getCustomChar(asciiChar);
					
	return (dp != -1 && pos == dp) ? digit + DECIMAL_POINT  : digit;
}
//------------------------------------------------------------------------------
char getCustomChar(char asciiChar)
{
	char i = 0, digit = 0x00;
  
	while(chars[i])
	{
		 if(toupper(asciiChar) == chars[i])
		 {
		   digit = charCode[i]; 
			 break;
		 }
		 i++;
	}	
					
	return digit;			
}
//------------------------------------------------------------------------------
signed char findPosChar(char chars[], char toFind)
{
	signed char i = 0, pos = -1;
	
	for(i = 0; i < strlen(chars); i++)
  {
    if(chars[i] == toFind)
		{
			pos = i - 1;
			break;
		}
  }
	
	return pos;
}
//------------------------------------------------------------------------------
#endif	