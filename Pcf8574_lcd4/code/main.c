#include<reg52.h>
#include <stdio.h>
#include <stdlib.h>
#include <./assets/LM75/LM75.h>
#include "assets/lcd/LCD_Serial.h"
//------------------------------------------------------------------------------
float tempr;
char out[30];
//------------------------------------------------------------------------------
int main() 
{
  LCD_init(0x4E);       // Expander Address  
  LM75_init();
	
  while(1)
  {
		tempr = LM75_read(TEMPERATURE_ADDRESS);
		sprintf(out, "Tempr: %3.2f%cC", tempr, DEG_SYMBOL);  
		LCD_string(0, 0, out);
  }
}
//------------------------------------------------------------------------------