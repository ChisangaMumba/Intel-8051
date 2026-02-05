#include<reg52.h>
#include <./assets/dht22/dht22.h>
#include <./assets/TM1637/TM1637.h>
//------------------------------------------------------------------------------
unsigned char str[12];
unsigned char sensorData[5];
signed int hum, tempr;
//------------------------------------------------------------------------------
int main() 
{	     
  TM1637_init(7);
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
			TM1637_displayText("Error");
		}
		else
			{
				hum = dht22_getHumidity(sensorData);
				tempr = dht22_getTemperature(sensorData);
				
				if(modeNum == 0 || modeNum == 1)
						sprintf(str, "%5.1f°%c", calcTempr(tempr), (modeNum == 0) ? 'C' : 'F');
				else
					  if(modeNum == 2)
								sprintf(str, "%6.1f%c", (float) hum/10, '%');
				
				TM1637_displayText(str);
			}
			__delay_ms(100);
  }
}
//------------------------------------------------------------------------------
