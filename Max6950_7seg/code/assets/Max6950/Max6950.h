#ifndef MAX6950_H
#define	MAX6950_H
//------------------------Dot Matrix LED  Driver--------------------------------
#include "../Soft_SPI/Soft_SPI.h"
#include "MAX6950_Prototypes.h"
//------------------------------------------------------------------------------
void MAX6950_init()
{
  SPI_init();
  
  MAX6950_write(DECODE_MODE_REG, DISABLE_DECODE);    
  MAX6950_write(INTESITY_REG, BRIGHTNESS);     
  MAX6950_write(SCAN_LIMIT_REG, SCAN_ALL_DIGITS);
  MAX6950_write(SHUTDOWN_REG, NORMAL_OPERATION);
}
//------------------------------------------------------------------------------
void MAX6950_write(char reg, signed char data_)
{
  CS1 = 0; 
  
  SPI_write(reg); 
  SPI_write(data_); 
  
  CS1 = 1;
}
//------------------------------------------------------------------------------
void MAX6950_displayNumber(float number)
{   
  char strNum[8]; 
	sprintf(strNum,"%6.2f",number);
  
	MAX6950_displayText(strNum);
}
//------------------------------------------------------------------------------
void MAX6950_displayText(char text[])
{ 
	char pos = 0, i, dp;  //dp: decimal point
	
	dp = findPosChar(text, '.');
	
  for(i = 0; i < strlen(text); i++)
  {   
    char asciiChar = text[i];  
		
		if(asciiChar != '.')
		{
			char digit = getDigit(pos, dp, asciiChar);
			
			MAX6950_write(DISPLAY_REG0 + pos, digit);
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