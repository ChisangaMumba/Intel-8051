#include<reg52.h>
#include <stdio.h>
#include <stdlib.h>
#include <./assets/LM75/LM75.h>
#include "assets/lcd/LCD_Serial.h"
//------------------------------------------------------------------------------
float tempr;
char str[18];
//------------------------------------------------------------------------------
int main() 
{
  LCD_init();      
  LM75_init();
	LCD_string(0, 4, "JHD1214");
	
  while(1)
  {
		tempr = LM75_read(TEMPERATURE_ADDRESS);
		sprintf(str, "Temp: %5.1f%cC", tempr, DEG_SYMBOL);  
		
		LCD_string(1, 0, str);
		__delay_ms(100);
  }
}
//------------------------------------------------------------------------------