#include<reg52.h>
#include <stdio.h>
#include <./assets/dht22/dht22.h>
#include <./assets/ht16k33/ht16k33.h>
//------------------------------------------------------------------------------
unsigned char str[12];
unsigned char sensorData[5];
int hum, tempr;
//------------------------------------------------------------------------------
int main() 
{	      
  ht16k33_init();
	dht22_init();
	
  while(1)
  { 
		oneWire_start();
		
		if(oneWire_getResponse())
		{	
			dht22_getSensorData(sensorData);
		}
		
		if(dht22_isChecksumInvalid(sensorData))
		{
			ht16k33_displayText("Error");
		}
		else
			{
				hum = dht22_getHumidity(sensorData);
				tempr = dht22_getTemperature(sensorData);
				
				if(modeNum == 0 || modeNum == 1)
						sprintf(str, "%7.1f°%c", calcTempr(tempr), (modeNum == 0) ? 'C' : 'F');
				else
					  if(modeNum == 2)
								sprintf(str, "%8.1f%c", (float) hum/10, '%');
			
				ht16k33_displayText(str);
				
			}		
			__delay_ms(100);
  }
}
//------------------------------------------------------------------------------