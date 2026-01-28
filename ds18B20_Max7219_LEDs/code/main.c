#include<reg52.h>
#include <stdio.h>
#include <stdlib.h>
#include "assets/delay/delay.h"
#include <./assets/ds18b20/ds18b20.h>
#include <./assets/MAX7219/MAX7219.h>
//------------------------------------------------------------------------------
char str[10];  
signed int tempr = 0;
//------------------------------------------------------------------------------
int main() 
{	  
  MAX7219_init(SCAN_ALL_DIGITS);
  ds18b20_init();
	
  while(1)
  { 
		tempr = ds18b20_read();
		tempr = (signed int)(ds18b20_toFloat(tempr) * 100);

		sprintf(str, " %5i°%c", tempr, (tempMode == 0) ? 'c' : 'f');
		MAX7219_displayText(str);
		__delay_ms(200);
  }
}
//------------------------------------------------------------------------------