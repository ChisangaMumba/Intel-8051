#include<reg52.h>
#include <stdio.h>
#include <./assets/TC72/TC72.h>
#include <./assets/nokia/nokia_glcd.h>
//------------------------------------------------------------------------------
signed int tempr;
char str[20];
//------------------------------------------------------------------------------
int main() 
{	
	LCD_init();
	TC72_init();
	
	//LCD_image(img);
	LCD_string(0, 0, "Nokia 3310 LCD");
  while(1)
  { 
		tempr = TC72_readTempr();
		sprintf(str, "Temp: %6.2f%°C", calcTempr(tempr)); 
		
		LCD_string(3, 0, str);
  }
}
//------------------------------------------------------------------------------