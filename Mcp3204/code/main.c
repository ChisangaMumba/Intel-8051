//------------------------------------------------------------------------------
#include<reg52.h>
#include <stdio.h>
#include <./assets/delay/delay.h>
#include <./assets/stdint/stdint.h>
#include <./assets/mcp320x/mcp320x.h>
#include <./assets/max7219/max7219.h>
//------------------------------------------------------------------------------
float volts;
uint8_t str[12];
//------------------------------------------------------------------------------
int main(void) 
{
	max7219_init(SCAN_ALL_DIGITS);
	mcp320x_init();
	
	while(1)
	{
		// LM35 produces voltage equivalent to temperature
		volts = mcp320x_getVoltage(DIFFERENTIAL_MODE, 3);		// // DIFFERENTIAL_MODE or SINGLE_MODE

		sprintf(str, "%7.2f°C", volts * 100);
		max7219_displayText(str);
		
		__delay_ms(100);
	}
}
//------------------------------------------------------------------------------