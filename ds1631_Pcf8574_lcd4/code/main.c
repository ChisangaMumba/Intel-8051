#include<reg52.h>
#include <stdio.h>
#include <stdlib.h>
#include <./assets/ds1631/ds1631.h>
#include "assets/lcd/LCD_Serial.h"
//------------------------------------------------------------------------------
unsigned char addr = 0x90; // Temperature sensor device Address
int tempr;
unsigned char resNum;
char out[30];
//------------------------------------------------------------------------------
int main() 
{
  LCD_init(0x4E);       // Expander Address
  LCD_string(0,5,"DS1621");
  
  ds1631_init(addr, RES12_BIT); 
  resNum = ds1631_getResolutionNum(addr);	
  
	while(1)
  {
		tempr = ds1631_read2ByteReg(addr, TEMP_REG);
    
    sprintf(out, "Tempr: %3.4f%cC", toFloat(tempr, resNum), DEG_SYMBOL);
		LCD_string(1,0,out);  
		//__delay_ms(1000);
  }
}
//------------------------------------------------------------------------------