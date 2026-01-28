#include<reg52.h>
#include <stdio.h>
#include <stdlib.h>
#include <./assets/tc74/tc74.h>
#include "assets/lcd/LCD_Serial.h"
//------------------------------------------------------------------------------
signed char tempr;
char str[18];
//------------------------------------------------------------------------------
int main() 
{
  LCD_init(0x4E);										// Expander Address  
  TC74_init(NORMAL_MODE);						// NORMAL vs STANDBY mode
	LCD_string(0, 5, "TC74");
	
  while(1)
  {
		tempr = TC74_read(TEMPR_REG);
		
		sprintf(str, "Tempr: %3i%cC", (signed int)tempr, DEG_SYMBOL);  
		LCD_string(1, 0, str);
  }
}
//------------------------------------------------------------------------------