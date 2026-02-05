#ifndef MAX6950_H
#define	MAX6950_H
//------------------------Dot Matrix LED  Driver--------------------------------
#include "MAX6950_Prototypes.h"
//------------------------------------------------------------------------------
void MAX6950_init(char noChips)
{
  SPI_init();
  
	while(noChips)
			MAX6950_config(--noChips);
}
//------------------------------------------------------------------------------
void MAX6950_config(char chip)
{
	MAX6950_write(DECODE_MODE_REG, DISABLE_DECODE, chip);    
  MAX6950_write(INTESITY_REG, BRIGHTNESS, chip);     
  MAX6950_write(SCAN_LIMIT_REG, SCAN_ALL_DIGITS, chip);
  MAX6950_write(SHUTDOWN_REG, NORMAL_OPERATION, chip);
}
//------------------------------------------------------------------------------
void MAX6950_write(char reg, signed char data_, char chip)
{
	if(chip == 0)
	{
		CS1 = 0;
		
		SPI_write(reg); 
    SPI_write(data_); 
		
		CS1 = 1; 
	}
	else	 
			if(chip == 1)
			{
				CS2 = 0;
				
				SPI_write(reg); 
				SPI_write(data_); 
				
				CS2 = 1; 
			}	
}
//------------------------------------------------------------------------------
void MAX6950_displayNumber(signed long number)
{   
  char strNum[15]; 
	sprintf(strNum,"%6li",number);
  
	MAX6950_displayText(strNum);
}
//------------------------------------------------------------------------------
void MAX6950_displayText(char text[])
{ 
	char chrPos = 0, dp = '.', count = 0, i;  
	
	signed char dpPos = findPosChar(text, dp);  //dp: decimal point
	
  for(i = 0; i < strlen(text); i++)
  {   
    char chr = text[i];  
		
		if(chr != dp)
		{
			char chip = getChipNum(count++);
			
			writeChar(chr, chrPos, dpPos, chip);
			chrPos = (chrPos >= 4) ? 0 : chrPos + 1;
		}
  }
}
//------------------------------------------------------------------------------
void writeChar(char chr, char chrPos, signed char dpPos, char chip)
{
	char digit = getDigit(chrPos, dpPos, chr);
	
	MAX6950_write(DISPLAY_REG0 + chrPos, digit, chip);
}
//------------------------------------------------------------------------------
char getDigit(char charPos, signed char dpPos, char chr)
{
	char digit = 0;
	
	digit = (chr >= '0' && chr <= '9') ? digits[chr - '0'] : getCustomChar(chr);
					
	return (dpPos != -1 && charPos == dpPos) ? digit + DECIMAL_POINT  : digit;
}
//------------------------------------------------------------------------------
char getCustomChar(char chr)
{
	char i = 0, digit = 0x00;
  
	while(chars[i])
	{
		 if(toupper(chr) == chars[i])
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
char getChipNum(char charPos)
{
	char chipNum = 0;
	
	if(charPos >= 0 && charPos <= 4)								//Digits 0 - 4 are on chip 0
		chipNum = 0;
	else
			if(charPos >= 5 && charPos <= 9)						//Digits 5 - 9 are on chip 1
				chipNum = 1;
					
	return chipNum;
}
//------------------------------------------------------------------------------
#endif	