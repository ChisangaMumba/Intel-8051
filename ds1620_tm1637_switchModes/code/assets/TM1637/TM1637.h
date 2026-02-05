#ifndef TM1637_H
#define	TM1637_H
//------------------------------------------------------------------------------
#include "TM1637_prototypes.h"
//------------------------------------------------------------------------------
void TM1637_init(char level)
{
	twoWire_init();    
	TM1637_setBrightness(level); //Valid brightness values: 0 - 8. 0 = display off.
}
//------------------------------------------------------------------------------
void TM1637_displayNum(long number)
{    
	char strNum[10];
	sprintf(strNum, "%6li", number);
		
	TM1637_displayText(strNum);
}
//------------------------------------------------------------------------------
void TM1637_displayText(char text[])
{
	TM1637_command(DISPLAY_MODE);    
	TM1637_write(text);
}
//------------------------------------------------------------------------------
void TM1637_setBrightness(char level)
{    
	TM1637_command(DISPLAY_CTRL + level); // Valid brightness values: 0 - 8. 0 = display off.
}
//------------------------------------------------------------------------------
void TM1637_write(char text[])
{
	char pos = 0;
	signed char dp = findPosChar(text, '.'); //dp: decimal point
	
	TM1637_initSend(DISPLAY_REG0);
	
	while(*text)
	{  
		char chr = *text++;
		
		if(chr != '.')
		{
			writeChar(pos++, dp, chr);
		}
	}
	
	twoWire_stop();
}
//------------------------------------------------------------------------------
void TM1637_command(char command)
{
	TM1637_initSend(command);
	twoWire_stop();
}
//------------------------------------------------------------------------------
void TM1637_initSend(char command)
{
	twoWire_start();
	twoWire_write(command);
	twoWire_ack();
}
//------------------------------------------------------------------------------
void writeChar(char pos, signed char dp, char chr)
{
	char digit = getDigit(pos, dp, chr);
	
	twoWire_write(digit);
	twoWire_ack();
}
//------------------------------------------------------------------------------
char getDigit(char pos, signed char dp, char chr)
{
	char digit = 0;
	
	digit = (isdigit(chr)) ? digits[chr - '0'] : getCustomChar(chr);
					
	return (dp != -1 && pos == dp) ? digit + DECIMAL_POINT  : digit;
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
	
	for(i = 0; i < chars[i]; i++)
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
#endif	/* TM1637_H */