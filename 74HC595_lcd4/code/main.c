#include<reg52.h>
#include <stdio.h>
#include <./assets/TC72/TC72.h>
#include <./assets/Lcd/LCD_Serial.h>
//------------------------------------------------------------------------------
signed int tempr;
char out[30];
//------------------------------------------------------------------------------
int main() 
{	
	TC72_Init();
	LCD_init();
	
  while(1)
  { 
		tempr = TC72_ReadTempr();
		sprintf(out, "Tempr: %3.2f%cC", toFloat(tempr), DEG_SYMBOL);  
		LCD_string(0, 0, out);
  }
}
//------------------------------------------------------------------------------