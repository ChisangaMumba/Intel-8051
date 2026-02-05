#include<reg52.h>
#include <./assets/dht11/dht11.h>
#include <./assets/Max6953/Max6953.h>
//------------------------------------------------------------------------------
char str[6];
unsigned char sensorData[5];
int hum, tempr;
//------------------------------------------------------------------------------
int main() 
{	  
  MAX6953_init();    
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
			MAX6953_displayText(" Err");
		}
		else
				{
					hum = dht11_getHumidity(sensorData);
					tempr = dht11_getTemperature(sensorData);
					
					if(sensorMode == 0)
							sprintf(str, "%2u°C", tempr);
					else
							if(sensorMode == 1)
									sprintf(str, "%3u%c", hum, '%');
							
					MAX6953_displayText(str);
				}
		
		__delay_ms(100);
  }
}
//------------------------------------------------------------------------------