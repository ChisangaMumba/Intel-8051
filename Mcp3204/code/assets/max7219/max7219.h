#ifndef MAX7219_H
#define	MAX7219_H
//------------------------Dot Matrix LED  Driver--------------------------------
#include "max7219_prototypes.h"
sbit CS1   = P1^3;         // Chip Select 1
//------------------------------------------------------------------------------
void max7219_init(uint8_t scanSize)
{
  SPI_init();
     
	max7219_write(DECODE_MODE_REG, DISABLE_DECODE);    
  max7219_write(INTESITY_REG, BRIGHTNESS);     
  max7219_write(SCAN_LIMIT_REG, scanSize);     
  max7219_write(SHUTDOWN_REG, NORMAL_OPERATION);
}
//------------------------------------------------------------------------------
void max7219_write(uint8_t reg, uint8_t _data)
{
  CS1 = 0; 
  
  SPI_write(reg); 
  SPI_write(_data); 
  
  CS1 = 1;
}
//------------------------------------------------------------------------------
void max7219_displayNumber(int32_t number)
{   
	uint8_t strNum[10]; 
  sprintf(strNum,"%6li",number);
	
	max7219_displayText(strNum);
}
//------------------------------------------------------------------------------
void max7219_displayText(uint8_t text[])
{ 
	uint8_t chrPos = 0, i, chr;
	
	if(!isDpFound)	
		getDpPos(dpPos, text);
	
  for(i = 0; text[i]; i++)
  {   
    chr = text[i];  
		
		if((chr != '.') && (chr != 194))  // ascii 194 is an extra character created by the degree ° symbol 
		{
			writeChar(chr, chrPos, dpPos[chrPos]);
			chrPos++;
		}
  }
}
//------------------------------------------------------------------------------
void writeChar(uint8_t chr, uint8_t chrPos, int8_t dpPos)
{
	uint8_t digit = getDigit(chr, chrPos, dpPos);
	max7219_write(chrPos + 1, digit);
}
//------------------------------------------------------------------------------
uint8_t getDigit(uint8_t chr, uint8_t chrPos, int8_t dpPos)
{
	uint8_t digit = 0;
	
	digit = (isdigit(chr)) ? digits[chr - '0'] : getCustomChar(chr);
					
	return (dpPos != -1 && chrPos == dpPos) ? digit + DECIMAL_POINT  : digit;
}
//------------------------------------------------------------------------------
uint8_t getCustomChar(uint8_t chr)
{
	uint8_t i = 0, digit = 0x00;
  
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
void getDpPos(int8_t dpPos[], uint8_t chars[])
{
	uint8_t i, pos = 0; 
	
	for(i = 0; chars[i]; i++)
  {
    if(chars[i] == '.')
		{
			dpPos[pos-1] = pos - 1;
			
			if(!isDpFound)
				isDpFound = 1;
		}
		else
				{
					pos++;
				}
  }
}
//------------------------------------------------------------------------------
#endif	