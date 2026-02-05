#ifndef SAA1064_H
#define	SAA1064_H
//------------------------------------------------------------------------------
#include "SAA1064_prototypes.h"
//------------------------------------------------------------------------------
void SAA1064_init()
{     
	I2C_init();            
 
	I2C_start();
	
	I2C_write(SAA1064_ADDRESS);   
	I2C_write(CONTROL_REG);    
	I2C_write(DEVICE_CONFIG);    
	
	I2C_stop();
}
//------------------------------------------------------------------------------
void SAA1064_displayInt(signed int number)
{
	char strNum[6];
  sprintf(strNum,"%4i",number);
	
	SAA1064_displayText(strNum);
}
//------------------------------------------------------------------------------
void SAA1064_displayFloat(float number)
{
	char strNum[6];
  sprintf(strNum,"%5.1f",number);
	
	SAA1064_displayText(strNum);
}
//------------------------------------------------------------------------------
void SAA1064_displayText(char text[])
{ 
	I2C_start();
	
	I2C_write(SAA1064_ADDRESS); //Device address
	I2C_write(DISPLAY_REG);     //Display data_ start address. Auto increments on every write.
	SAA1064_write(text);
	
	I2C_stop();
}
//------------------------------------------------------------------------------
void SAA1064_write(char text[])
{
	char charPos = 0, dp = '.';
	signed char dpPos = findPosChar(text, dp) - 1;  //dp: decimal point
	
	text = get_lastCharAddr(text); //To write the Data backwards 
	
	while(*text)
	{
		char chr = *text--;
		
		if(chr != dp)
				writeChar(charPos++, dpPos, chr);   
	}	
}
//------------------------------------------------------------------------------
void writeChar(char chrPos, signed char dpPos, char chr)
{    
	char digit = getDigit(chrPos, dpPos, chr); //ascii to 7 seg

	I2C_write(digit);                     
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
char* get_lastCharAddr(char text[])
{
  char lastAddr =  strlen(text) - 1;  
  
  return text + lastAddr;
}
//------------------------------------------------------------------------------
#endif	/* SAA1064_H */