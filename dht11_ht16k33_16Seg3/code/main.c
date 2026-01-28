#include<reg52.h>
#include <stdio.h>
#include <./assets/dht11/dht11.h>
#include <./assets/ht16k33/ht16k33.h>
//------------------------------------------------------------------------------
unsigned char str[12];
unsigned char sensorData[5];
int hum, tempr;
//------------------------------------------------------------------------------
int main() 
{	      
  ht16k33_init();
	dht11_init();
	
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
				if(modeNum == 0 || modeNum == 1)
					sprintf(str, "%2u°%c", dht11_getTemperature(sensorData), (modeNum == 0) ? 'C' : 'F');
				else
					  if(modeNum == 2)
							sprintf(str, " %2u%c", dht11_getHumidity(sensorData), '%');
					
				
				ht16k33_displayText(str);
			}
			__delay_ms(100);
  }
}
//------------------------------------------------------------------------------