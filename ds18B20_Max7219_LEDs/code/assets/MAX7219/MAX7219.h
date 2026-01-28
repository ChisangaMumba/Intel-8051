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
	char strNum[15]; 
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
    MAX7219_write( pos+1, getDigit(pos,i) );
  }
}
//------------------------------------------------------------------------------
char getDigit(char pos, char asciiChar)
{
	char digit = 0, dp = 3;
	
	if(asciiChar >= '0' && asciiChar <= '9') 
	{
		unsigned char i = asciiChar - '0';
		digit = (pos == dp) ? (digits[i] + DECIMAL_POINT) : digits[i] ;
	}
	else
			if(asciiChar == '-')
			{
					digit = (pos == dp) ? (digits[0] + DECIMAL_POINT) : 0x01;  //0x01 - minus symbol
			}
			else
					if(asciiChar == ' ')
					{
							digit = (pos == dp) ? (digits[0] + DECIMAL_POINT) : 0x00; //0x00 - blank. used for leading zero suppression
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
	char digit = 0x00;
						
	if(toupper(asciiChar) == 'C')
		digit = 0x4E; 
	else
			if(toupper(asciiChar) == 'F')
				digit = 0x47;
			else
					if(asciiChar == '°')
						digit = 0x63;
					
	return digit;			
}
//------------------------------------------------------------------------------
#endif	