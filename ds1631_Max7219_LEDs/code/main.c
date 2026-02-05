#include<reg52.h>
#include <stdio.h>
#include <stdlib.h>
#include <./assets/ds1631/ds1631.h>
#include <./assets/MAX7219/MAX7219.h>
//------------------------------------------------------------------------------
unsigned char addr = 0x90; // Temperature sensor device Address
char str[12]; 
unsigned char resNum;
signed int tempr;
//------------------------------------------------------------------------------
int main() 
{	  
  MAX7219_init(SCAN_ALL_DIGITS);
  ds1631_init(addr, RES12_BIT); 
  resNum = ds1631_getResolutionNum(addr);
	
  while(1)
  { 	
		tempr = ds1631_read2ByteReg(addr, TEMP_REG);
		
		sprintf(str, "%7.3f°%c", toFloat(tempr, resNum), (tempMode == 0) ? 'c' : 'f'); 
		MAX7219_displayText(str);
  }
}
//------------------------------------------------------------------------------