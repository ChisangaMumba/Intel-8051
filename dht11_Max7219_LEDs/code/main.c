#include<reg52.h>
#include <stdio.h>
#include <stdlib.h>
#include "assets/delay/delay.h"
#include <./assets/dht11/dht11.h>
#include <./assets/MAX7219/MAX7219.h>
//------------------------------------------------------------------------------
char str[12];  
unsigned char sensorData[5];
int hum, tempr;
//------------------------------------------------------------------------------
int main() 
{	  
  MAX7219_init(SCAN_ALL_DIGITS);
  dht11_init();;
	
  while(1)
  { 	  
		oneWire_start();
		
		if(oneWire_getResponse())
		{	
			dht11_getSensorData(sensorData);
		}
		
		if(dht11_isChecksumValid(sensorData))
		{
			MAX7219_displayText("Error");
		}
		else
			{
				hum = dht11_getHumidity(sensorData);
				tempr = dht11_getTemperature(sensorData);
				sprintf(str, "%2u%c%3u°%c", hum, '%', tempr, (tempMode == 0) ? 'c' : 'f' );
				
				MAX7219_displayText(str);
			}
			__delay_ms(100);
  }
}
//------------------------------------------------------------------------------