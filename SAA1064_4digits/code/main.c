#include<reg52.h>
#include <stdio.h>
#include <string.h>
#include <./assets/mcp9800/mcp9800.h>
#include <./assets/SAA1064/SAA1064.h>
//------------------------------------------------------------------------------
unsigned char addr = 0x90; // Temperature sensor device Address
char resInd, str[6];
int rawData;
float tempr;
//------------------------------------------------------------------------------
int main() 
{	      
  SAA1064_init();
	mcp9800_init(addr, RES09_BIT); 
	resInd = mcp9800_getResolutionNum(addr);

  while(1)
  { 
    rawData = mcp9800_read(addr, TEMP_REG);
		tempr = calcTemp(rawData, resInd);
    
		//SAA1064_displayFloat(tempr);
		//SAA1064_displayFloat(3.4);
		SAA1064_displayInt(4);
		__delay_ms(100);
  }
}
//------------------------------------------------------------------------------