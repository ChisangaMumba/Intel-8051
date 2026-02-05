#ifndef MAX6953_H
#define	MAX6953_H
//------------------------Dot Matrix LED  Driver--------------------------------
#include "MAX6953_Prototypes.h"
//------------------------------------------------------------------------------
void MAX6953_init()
{  
	char noChips = 2;
	
	I2C_init(); 
	
	while(noChips)
			MAX6953_config(--noChips);
}
//------------------------------------------------------------------------------
void MAX6953_config(char chip)
{  
  MAX6953_write(DECODE_MODE_REG, DECODE_ALL, chip);    //Decodes ascii characters
  MAX6953_write(INTESITY_REG10, BRIGHTNESS, chip); 
  MAX6953_write(INTESITY_REG32, BRIGHTNESS, chip);
  MAX6953_write(SCAN_LIMIT_REG, SCAN_LOW_NIBBLE, chip);
  MAX6953_write(SHUTDOWN_REG, NORMAL_OPERATION, chip);
}
//------------------------------------------------------------------------------
void MAX6953_write(char reg, signed char data_, char chip)
{
	char addr;

	if(chip == 0 || chip == 1)
			addr = (chip == 0) ? DEVICE_ADDRESS0 : DEVICE_ADDRESS1;
			
  I2C_start();
 
  I2C_write(addr);
  I2C_write(reg); 
  I2C_write(data_);
  
  I2C_stop();
}
//------------------------------------------------------------------------------
void MAX6953_displayInt(signed long number)
{   
	char strNum[10]; 
  sprintf(strNum, "%6li", number);
  
	MAX6953_displayText(strNum);
}
//------------------------------------------------------------------------------
void MAX6953_displayText(char text[])
{
	char chrPos = 0, i;
		
	for(i = 0; text[i] != '\0'; i++)
  {  
		writeChar(chrPos, text[i], i);
		chrPos = (chrPos >= 3) ? 0 : chrPos + 1;
  }
}
//------------------------------------------------------------------------------
void writeChar(char chrPos, char chr, char count)
{
	char chip;
	
	if(chr & 0x80) 									//All non-standard ascii chars are above 128
		chr = getCustomChar(chr);
	
	chip = getChipNum(count);
	
	MAX6953_write(DISPLAY_REG0 + chrPos, chr, chip);
}
//------------------------------------------------------------------------------
char getCustomChar(char chr)
{
	char i = 0, digit = 0x00;
  
	while(customChar[i])
	{
		 if(chr == customChar[i])
		 {
		   digit = charCode[i]; 
			 break;
		 }
		 i++;
	}	
					
	return digit;			
}
//------------------------------------------------------------------------------
char getChipNum(char charPos)
{
	char chipNum = 0;
	
	if(charPos >= 0 && charPos <= 3)								//Digits 0 - 3 are on chip 0
		chipNum = 0;
	else
			if(charPos >= 4 && charPos <= 7)						//Digits 4 - 7 are on chip 1
				chipNum = 1;
					
	return chipNum;
}
//------------------------------------------------------------------------------
#endif	