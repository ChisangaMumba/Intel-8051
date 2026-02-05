#ifndef HT16K33_H
#define	HT16K33_H
//------------------------------------------------------------------------------
#include <./assets/i2c/i2c.h>
#include <./assets/delay/delay.h>
#include <ctype.h>
#include "ht16k33_prototypes.h"
//------------------------------------------------------------------------------
void ht16k33_init()
{     
	I2C_init();            
	
	__delay_ms(5);               //Required after Power On reset to give time to initialize device
 
	ht16k33_on();
	ht16k33_setBrightness(15);   //Valid values from 0 - 15
	ht16k33_blink(0);            //Blink OFF
}
//------------------------------------------------------------------------------
void ht16k33_on()
{
	I2C_start();
	
	I2C_write(HT16K33_ADDRESS);
	I2C_write(OSCILLATOR_ON);          
	
	I2C_stop();
}
//------------------------------------------------------------------------------
void ht16k33_setBrightness(unsigned char num)
{   
 char level = ( num <= 15 ) ? num : 1;  //Default to 1 if invalid value is provided
	
 I2C_start();
 
 I2C_write(HT16K33_ADDRESS);
 I2C_write(DIGITAL_DIM | level);  // Dimming command. valid values are 0 - 15
 
 I2C_stop();
}
//------------------------------------------------------------------------------
void ht16k33_blink(char _data)
{
	I2C_start();
	
	I2C_write(HT16K33_ADDRESS);
	I2C_write(DISPLAY_SETUP | (_data << 1));  // Blinking / blanking command
	
	I2C_stop();
}
//------------------------------------------------------------------------------
void ht16k33_displayNum(signed long number)
{
	char strNum[10];
	sprintf(strNum,"%6li",number);
	
	ht16k33_displayNumText(strNum);
}
//------------------------------------------------------------------------------
void ht16k33_displayNumText(char text[])
{
	I2C_start();
	
	I2C_write(HT16K33_ADDRESS);
	I2C_write(DISPLAY_MEMORY);     //Display _data start address. Auto increments on every write.
	ht16k33_write(text);
	
	I2C_stop();
}
//------------------------------------------------------------------------------
void ht16k33_write(char text[])
{
	char pos = 0;  
	signed char dp = findPosChar(text, '.'); //dp: decimal point
	
	while(*text)
	{
		char asciiChar = *text++;
		
		if(asciiChar != '.')
			ht16k33_char(pos++, dp, asciiChar);
	}
}
//------------------------------------------------------------------------------
void ht16k33_char(char pos, signed char dp, char asciiChar)
{    
	char digit = getDigit(pos, dp, asciiChar); //ascii to 7 seg

	I2C_write(digit);               //Lower byte  (D7 - D0)
	I2C_write(0);                   //Higher byte (D15 - D8) Unused in 7 seg display
}
//------------------------------------------------------------------------------
//          ascii to 7 segment
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
#endif	/* HT16K33_H */

