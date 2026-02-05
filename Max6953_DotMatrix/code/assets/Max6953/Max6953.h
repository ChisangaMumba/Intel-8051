#ifndef MAX6953_H
#define	MAX6953_H
//------------------------Dot Matrix LED  Driver--------------------------------
#include <string.h>
#include <stdio.h>
#include "../i2c/I2C.h"
#include "MAX6953_Prototypes.h"
//------------------------------------------------------------------------------
void MAX6953_init()
{  
  MAX6953_write(DECODE_MODE_REG, DECODE_ALL);    //Decodes ascii characters
  MAX6953_write(INTESITY_REG10, BRIGHTNESS); 
  MAX6953_write(INTESITY_REG32, BRIGHTNESS);
  MAX6953_write(SCAN_LIMIT_REG, SCAN_LOW_NIBBLE);
  MAX6953_write(SHUTDOWN_REG, NORMAL_OPERATION);
}
//------------------------------------------------------------------------------
void MAX6953_write(char reg, signed char data_)
{
  I2C_start();
 
  I2C_write(DEVICE_ADDRESS);
  I2C_write(reg); 
  I2C_write(data_);
  
  I2C_stop();
}
//------------------------------------------------------------------------------
void MAX6953_displayNumber(signed int number)
{   
	char strNum[6]; 
  sprintf(strNum, "%4i", number);
  
	MAX6953_displayText(strNum);
}
//------------------------------------------------------------------------------
void MAX6953_displayText(char text[])
{
	char i, chr;
	
	I2C_start();

  I2C_write(DEVICE_ADDRESS);
  I2C_write(DISPLAY_REG0);					//auto_ increments on every write
  
	for(i = 0; i < strlen(text); i++)
  {    
		chr = text[i];
		
		if(chr & 0x80) 									//All non-standard ascii chars are above 128
			getCustomChar(chr);
		
		I2C_write(chr);
  }
	
	I2C_stop();
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