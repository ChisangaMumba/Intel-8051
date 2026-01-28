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
   char level = ( num <= 15 ) ? num : 1;
    
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
void ht16k33_displayNum(signed long int number)
{
	char strNum[12];
	sprintf(strNum, "%8li", number);
	
	ht16k33_displayText(strNum);
}
//------------------------------------------------------------------------------
void ht16k33_displayText(char text[])
{
    I2C_start();
    
    I2C_write(HT16K33_ADDRESS);
    I2C_write(DISPLAY_MEMORY);     //Display data start address. Auto increments on every write.
    ht16k33_write(text);
    
    I2C_stop();
}
//------------------------------------------------------------------------------
void ht16k33_write(char text[])
{
    while(*text)
    {
       ht16k33_char(*text++);
    }
}
//------------------------------------------------------------------------------
void ht16k33_char(char _data)
{
	 unsigned int asciiChar = 0;
   char i = _data - ' ';            //minus first 32 non-printable ascii characters (see ascii table)

	//Standard ascii chars range 32 - 127 or 0 - 95 (after subtraction). degree symbol num ° is 144 after subtraction
	asciiChar = (i >= 0 && i <= 95) ? font[i] : custom_chars[0];  //Custom _char is ° symbol
	
	I2C_write(asciiChar);							//Lower byte  (D7 - D0)
	I2C_write(asciiChar>>8);					//Higher byte (D15 - D8)
}
//------------------------------------------------------------------------------
#endif	/* HT16K33_H */

