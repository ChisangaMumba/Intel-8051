#include<reg52.h>
#include <stdio.h>
#include <stdlib.h>
#include "assets/TC72/TC72.h"
#include "assets/lcd/LCD_Serial.h"
//------------------------------------------------------------------------------
signed int tempr;
char out[30];
//------------------------------------------------------------------------------
int main() 
{
  LCD_init();  
  TC72_Init();
	
  while(1)
  {
		tempr = TC72_ReadTempr();
		sprintf(out, "Tempr: %3.2f%cC", toFloat(tempr), DEG_SYMBOL);  
		LCD_string(0, 0, out);
  }
}
//------------------------------------------------------------------------------