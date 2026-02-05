#include<reg52.h>
#include <stdio.h>
#include <stdlib.h>
#include "assets/tc77/tc77.h"
#include "assets/lcd/LCD_Serial.h"
//------------------------------------------------------------------------------
char str[18];
//------------------------------------------------------------------------------
int main() 
{
  LCD_init();  
  TC77_init();
	LCD_string(0, 7, "TC77");
	
  while(1)
  {		
		sprintf(str, "Temp: %3.4f%cC", toFloat(TC77_read()), DEG_SYMBOL);  
		LCD_string(1, 0, str);
  }
}
//------------------------------------------------------------------------------