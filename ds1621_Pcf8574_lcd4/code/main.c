#include<reg52.h>
#include <stdio.h>
#include <stdlib.h>
#include <./assets/ds1621/ds1621.h>
#include "assets/lcd/LCD_Serial.h"
//------------------------------------------------------------------------------
unsigned char addr = 0x90; // Temperature sensor device Address
float tempr;
char out[30];
//------------------------------------------------------------------------------
int main() 
{
  LCD_init(0x4E);       // Expander Address  
  ds1621_init(addr);    
	LCD_string(0,5,"DS1621");
	
  while(1)
  {
		tempr = ds1621_read2ByteReg(addr, TEMP_REG);
    
    sprintf(out,"Tempr: %3.2f%cC",toFloat(tempr), DEG_SYMBOL);
    LCD_string(1,0,out);  
  }
}
//------------------------------------------------------------------------------