//------------------------------------------------------------------------------
#include <reg52.h>							 //including _sfr registers for ports of the controller
#include <stdio.h>
#include <./assets/lcd4/lcd4.h>
#include <./assets/dht22/dht22.h>
//------------------------------------------------------------------------------
unsigned char str[18];
unsigned char sensorData[5];
signed int hum, tempr;
//------------------------------------------------------------------------------
int main()
{
	LCD_init();	
	
  while(1)
  {          
		oneWire_start();
		
		if(oneWire_getResponse())
		{	
			dht22_getSensorData(sensorData);
		}
		
		if(dht22_isChecksumInvalid(sensorData))
		{
			LCD_string(0,0,"Error");
		}
		else
			{
				hum = dht22_getHumidity(sensorData);
				tempr = dht22_getTemperature(sensorData);
				
				sprintf(str, "Humd: %4.1f%c", (float) hum/10, '%');
				LCD_string(0, 0, str);
				
        sprintf(str, "Tempr: %5.1f%cC", calcTempr(tempr), 223);
				LCD_string(1, 0, str);
			}
			__delay_ms(100);
  }
}
//------------------------------------------------------------------------------