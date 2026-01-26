//------------------------------------------------------------------------------
#include<reg52.h>
#include <stdio.h>
#include <./assets/delay/delay.h>
#include <./assets/stdint/stdint.h>
#include <./assets/mcp320x/mcp320x.h>
#include <./assets/uart/uart.h>
//------------------------------------------------------------------------------
float volts;
uint8_t str[30];
const uint16_t CH = 3;	// Channel
//------------------------------------------------------------------------------
int main(void) 
{
	uart_init();
	mcp320x_init();
		
	while(1)
	{
		// LM35 produces voltage equivalent to temperature
		volts = mcp320x_getVoltage(DIFFERENTIAL_MODE, CH); // DIFFERENTIAL_MODE or SINGLE_MODE 				
		
		sprintf(str, "Channel:%2u, Temp:%6.2f°C\r", CH, volts * 100); 
		uart_msg(str);
		
		__delay_ms(500);	
	}
}
//------------------------------------------------------------------------------