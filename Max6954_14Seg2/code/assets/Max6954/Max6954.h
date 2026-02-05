#ifndef MAX6954_H
#define	MAX6954_H
//------------------------Dot Matrix LED  Driver--------------------------------
#include "MAX6954_Prototypes.h"
//------------------------------------------------------------------------------
void MAX6954_init()
{
  SPI_init();
	
  MAX6954_write(DECODE_MODE_REG, DECODE_ALL);         //Decode ascii characters          
	MAX6954_write(GLOBAL_INTESITY_REG, BRIGHTNESS); 
  MAX6954_write(SCAN_LIMIT_REG, SCAN_ALL_DIGITS);
  MAX6954_write(SHUTDOWN_REG, NORMAL_OPERATION);
	MAX6954_write(DIGIT_TYPE_REG, MODE_14_SEG);
}
//------------------------------------------------------------------------------
void MAX6954_write(unsigned char reg, unsigned char data_)
{
  CS = 0; 
  
  SPI_write(reg); 
  SPI_write(data_); 
		
  CS = 1;
}
//------------------------------------------------------------------------------
void MAX6954_displayNumber(long number)
{   
	char strNum[15]; 
  sprintf(strNum, "%6li", number);
  
	MAX6954_displayText(strNum);
}
//------------------------------------------------------------------------------
void MAX6954_displayText(char text[])
{
	char chrPos = 0, i, chr;
	signed char dpPos = findPosChar(text, '.'); //dp: decimal point
						
  for(i = 0; i < strlen(text); i++)
  {  
		chr = text[i];								
		
		if(chr != '.')						
			writeChar(chr, chrPos++, dpPos); 
  }
}
//------------------------------------------------------------------------------
void writeChar(char chr, char chrPos, signed char dpPos)
{
	if(chr & 0x80)									//All non-standard ascii chars are above 128
		chr = getCustomChar(chr); 
	
	if(dpPos != -1 && chrPos == dpPos)
	{
		chr +=  DECIMAL_POINT; 
	}

	MAX6954_write(DISPLAY_REG0 + chrPos, chr);
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