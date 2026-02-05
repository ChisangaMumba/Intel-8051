#include<reg52.h>
#include <./assets/delay/delay.h>
#include <./assets/dht22/dht22.h>
#include <./assets/Max6954/Max6954.h>
//------------------------------------------------------------------------------
char str[15];
unsigned char sensorData[5];
int hum, tempr;
//------------------------------------------------------------------------------
int main() 
{	  
  MAX6954_init();    
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
			MAX6954_displayText(" Err");
		}
		else
				{
					hum = dht22_getHumidity(sensorData);
					tempr = dht22_getTemperature(sensorData);
				
					if(modeNum == 0 || modeNum == 1)
							sprintf(str, "%6.1f°%c", calcTempr(tempr), (modeNum == 0) ? 'C' : 'F');
					else
							if(modeNum == 2)
									sprintf(str, "%7.1f%c", (float) hum/10, '%');
						
					MAX6954_displayText(str);
				}
		
		__delay_ms(100);
  }
}
//------------------------------------------------------------------------------