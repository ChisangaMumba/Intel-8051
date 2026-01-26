#ifndef HT16K33_H
#define	HT16K33_H
//------------------------------------------------------------------------------
#include <./assets/i2c/i2c.h>
#include <./assets/delay/delay.h>
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
void ht16k33_displayNum(signed int number)
{
	char strNum[10];
	sprintf(strNum,"%4i",number);
	
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
	
	while(*text)
	{
		 ht16k33_char(*text++, pos++);
	}
}
//------------------------------------------------------------------------------
void ht16k33_char(char asciiChar, char pos)
{    
	char digit = getDigit(asciiChar, pos); //ascii to 7 seg

	I2C_write(digit);               //Lower byte  (D7 - D0)
	I2C_write(0);                   //Higher byte (D15 - D8) Unused in 7 seg display
}
//------------------------------------------------------------------------------
//          ascii to 7 segment
char getDigit(char asciiChar, char pos)  
{
	char digit = 0;
	
	if(asciiChar >= '0' && asciiChar <= '9')
	{
			char i = asciiChar - '0';
			digit = (pos == 1 || pos == 3) ? (digits[i] + DECIMAL_POINT) : digits[i]; //ANDing with DECIMAL_POINT Turns off MSB
	}
	else
			if(asciiChar == '-')
			{
					digit = (pos == 1 || pos == 3) ? (digits[0] + DECIMAL_POINT) : 0x40;  //0x40 - minus symbol
			}
			else
					if(asciiChar == ' ')
					{
							digit = (pos == 1 || pos == 3) ? (digits[0] + DECIMAL_POINT) : 0x00; //0x00 - blank. used for leading zero suppression
					}
	
	return digit;
}
//------------------------------------------------------------------------------
#endif	/* HT16K33_H */

