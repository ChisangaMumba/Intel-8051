#include<reg52.h>
#include <stdio.h>
#include <stdlib.h>
#include "assets/delay/delay.h"
#include <./assets/tc77/tc77.h>
#include <./assets/MAX7219/MAX7219.h>
//------------------------------------------------------------------------------
char str[18];  
signed int tempr;
//------------------------------------------------------------------------------
int main() 
{	  
  MAX7219_init(SCAN_ALL_DIGITS);
  TC77_init();
	
  while(1)
  { 	
		tempr = TC77_read();
 
		sprintf(str, "%7.3f°%c", toFloat(tempr), (tempMode == 0) ? 'c' : 'f'); 
		MAX7219_displayText(str);
  }
}
//------------------------------------------------------------------------------