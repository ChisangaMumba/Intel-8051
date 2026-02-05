#include<reg52.h>
#include <./assets/dht11/dht11.h>
#include <./assets/Max6952/Max6952.h>
//------------------------------------------------------------------------------
char str[6];
unsigned char sensorData[5];
int hum, tempr;
//------------------------------------------------------------------------------
int main() 
{	  
  MAX6952_init(3);    
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
			MAX6952_displayText(" Err");
		}
		else
				{
					hum = dht11_getHumidity(sensorData);
					tempr = dht11_getTemperature(sensorData);
					
					sprintf(str, "%2u%c%3u°%c", hum, '%', tempr, (tempMode == 0) ? 'C' : 'F');		
					MAX6952_displayText(str);
				}
		
		__delay_ms(100);
  }
}
//------------------------------------------------------------------------------