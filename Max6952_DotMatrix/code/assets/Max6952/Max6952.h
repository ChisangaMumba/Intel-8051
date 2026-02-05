#ifndef MAX6952_H
#define	MAX6952_H
//------------------------Dot Matrix LED  Driver--------------------------------
#include <string.h>
#include <stdio.h>
#include "../Soft_SPI/Soft_SPI.h"
#include "MAX6952_Prototypes.h"
//------------------------------------------------------------------------------
void MAX6952_init()
{
  SPI_init();
  
  MAX6952_write(DECODE_MODE_REG, DECODE_ALL);    //Decodes ascii characters
  MAX6952_write(INTESITY_REG10, BRIGHTNESS); 
  MAX6952_write(INTESITY_REG32, BRIGHTNESS);
  MAX6952_write(SCAN_LIMIT_REG, SCAN_LOW_NIBBLE);
  MAX6952_write(SHUTDOWN_REG, NORMAL_OPERATION);
}
//------------------------------------------------------------------------------
void MAX6952_write(char reg,signed char data_)
{
  CS = 0; 
  
  SPI_write(reg); 
  SPI_write(data_); 
  
  CS = 1;
}
//------------------------------------------------------------------------------
void MAX6952_displayNumber(signed int number)
{   
	char strNum[6]; 
  sprintf(strNum, "%4i", number);
  
	MAX6952_displayText(strNum);
}
//------------------------------------------------------------------------------
void MAX6952_displayText(char text[])
{
	char i, asciiChar;
	
  for(i = 0; i < strlen(text); i++)
  {    
		asciiChar = (text[i] & 0x80) ? getCustomChar(text[i]) : text[i]; //All non-standard ascii chars are above 128
		MAX6952_write( DISPLAY_REG0 + i, asciiChar);
  }
}
//------------------------------------------------------------------------------
char getCustomChar(char asciiChar)
{
	char i = 0, digit = 0x00;
  
	while(customChar[i])
	{
		 if(asciiChar == customChar[i])
		 {
		   digit = charCode[i]; 
			 break;
		 }
		 i++;
	}	
					
	return digit;			
}
//------------------------------------------------------------------------------
#endif	