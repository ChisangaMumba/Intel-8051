#include<reg52.h>
#include <stdio.h>
#include <./assets/delay/delay.h>
#include <./assets/ds1620/ds1620.h>
#include <./assets/Lcd/LCD_Serial.h>
//------------------------------------------------------------------------------
int tempH, tempL;
float tempF;
char str[30];
//------------------------------------------------------------------------------
int main(void) 
{	
	LCD_init();
	ds1620_init(25, 20); //Set thermostat high and low values
	
	tempH = ds1620_getTemp(READ_TH);
	tempL = ds1620_getTemp(READ_TL);
	
	sprintf(str, "TH:%3i°C,TL:%3i°C", tempH, tempL);
	LCD_string(0, 0, str);
	
  while(1)
  { 		
		tempF = ds1620_getTempFloat();
		sprintf(str, "Tempr:%5.1f°C", tempF);
		LCD_string(1, 0, str);
		
		__delay_ms(500);
  }
}
//------------------------------------------------------------------------------