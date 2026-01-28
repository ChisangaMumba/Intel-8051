#include<reg52.h>
#include <stdio.h>
#include <./assets/ds18b20/ds18b20.h>
#include <./assets/Lcd/LCD_Serial.h>
//------------------------------------------------------------------------------
unsigned char str[18];
signed int tempr = 0;
//------------------------------------------------------------------------------
int main() 
{	
	LCD_init();  
	LCD_string(0, 5, "DS18B20");;
	
  while(1)
  { 
		tempr = ds18b20_read();
			
		sprintf(str,"Temp: %8.4f°C", ds18b20_toFloat(tempr));     
		LCD_string(1,0,str);
		
		__delay_ms(200);
  }
}
//------------------------------------------------------------------------------