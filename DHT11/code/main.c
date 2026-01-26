//------------------------------------------------------------------------------
#include <reg52.h>							 //including _sfr registers for ports of the controller
#include <stdio.h>
#include <./assets/lcd4/lcd4.h>
#include <./assets/dht11/dht11.h>
//------------------------------------------------------------------------------
unsigned char str[20];
unsigned char sensorData[5];
//------------------------------------------------------------------------------
int main()
{
	LCD_init();	
	
  while(1)
  {          
		oneWire_start();
		
		if(oneWire_getResponse())
		{	
			dht11_getSensorData(sensorData);
		}
		
		if(dht11_isChecksumValid(sensorData))
		{
			LCD_string(0,0,"Error");
		}
		else
			{
				sprintf(str, "Humd: %2u%c", dht11_getHumidity(sensorData), '%');
				LCD_string(0,0, str);
				
        sprintf(str, "Tempr: %2u%cC", dht11_getTemperature(sensorData), 223);
				LCD_string(1,0, str);
			}
			__delay(100);
  }
}
//------------------------------------------------------------------------------