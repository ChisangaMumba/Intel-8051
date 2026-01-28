#include<reg52.h>
#include <stdio.h>
#include <./assets/dht11/dht11.h>
#include <./assets/ht16k33/ht16k33.h>
//------------------------------------------------------------------------------
unsigned char str[12];
unsigned char sensorData[5];
//------------------------------------------------------------------------------
int main() 
{	      
  ht16k33_init();
	
  while(1)
  { 
		oneWire_start();
		
		if(oneWire_getResponse())
		{	
			dht11_getSensorData(sensorData);
		}
		
		if(dht11_isChecksumValid(sensorData))
		{
			ht16k33_displayText("Error");
		}
		else
			{
				sprintf(str, "%2u%c %2u°C", dht11_getHumidity(sensorData), '%', dht11_getTemperature(sensorData));
				ht16k33_displayText(str);
			}
			__delay_ms(100);
  }
}
//------------------------------------------------------------------------------