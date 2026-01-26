#ifndef TM1637_H
#define	TM1637_H
//------------------------------------------------------------------------------
#include <stdio.h>
#include "../../assets/twoWire/twoWire.h"
#include "TM1637_prototypes.h"
//------------------------------------------------------------------------------
//Common Anode             0,    1,    2,    3,    4,    5,    6,    7,    8,   9
const char digits[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F };
//------------------------------------------------------------------------------
void TM1637_init(char level)
{
	twoWire_init();    
	TM1637_setBrightness(level); //Valid brightness values: 0 - 8. 0 = display off.
}
//------------------------------------------------------------------------------
void TM1637_displayNum(signed int number)
{    
	char strNum[10];
	sprintf(strNum, "%4i", number);
	
	TM1637_displayNumText(strNum);
}
//------------------------------------------------------------------------------
void TM1637_displayNumText(char text[])
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
	TM1637_initSend(DISPLAY_REG0);
	
	while(*text)
	{        
			twoWire_write( getDigit(pos++, *text++) );
			twoWire_ack();
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
char getDigit(char pos, char asciiChar)
{
	char i, digit = 0;
	
	if(asciiChar >= '0' && asciiChar <= '9')
	{
			i = asciiChar - '0'; //Get index 0 - 9
			digit = (pos == 1 || pos == 3) ? (digits[i] + DECIMAL_POINT) : digits[i];
	}
	else
			if(asciiChar == '-')
			{
					digit = (pos == 1 || pos == 3) ? (digits[0]  + DECIMAL_POINT) : 0x40;  //0x40 - minus symbol
			}
			else
					if(asciiChar == ' ')
					{
							digit = (pos == 1 || pos == 3) ? (digits[0] + DECIMAL_POINT) : 0x00; //0x00 - blank. used for leading zero suppression
					}
	
	return digit;
}
//------------------------------------------------------------------------------
#endif	/* TM1637_H */