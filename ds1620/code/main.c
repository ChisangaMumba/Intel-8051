//------------------------------------------------------------------------------
#include<reg52.h>							 //including _sfr registers for ports of the controller
#include <stdio.h>
#include <./assets/delay/delay.h>
#include <./assets/uart/uart.h>
#include <./assets/ds1620/ds1620.h>
//------------------------------------------------------------------------------
int tempH, tempL;
float tempF;
char str[30];
//------------------------------------------------------------------------------
int main(void) 
{		
	uart_init();
	ds1620_init(25, 20); //Set thermostat high and low values
	
	tempH = ds1620_getTemp(READ_TH);
	tempL = ds1620_getTemp(READ_TL);
	
	sprintf(str, "TH: %i°C, TL: %i°C\n\r", tempH, tempL);
	uart_msg(str);
	
	while(1)
	{
		tempF = ds1620_getTempFloat();
		
		sprintf(str, "Temperature: %5.1f°C\n\r", tempF);
		uart_msg(str);
		
		__delay_ms(500);
	}
}
//------------------------------------------------------------------------------
