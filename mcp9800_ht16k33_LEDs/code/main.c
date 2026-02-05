#include<reg52.h>
#include <stdio.h>
#include <string.h>
#include <./assets/mcp9800/mcp9800.h>
#include <./assets/ht16k33/ht16k33.h>
//------------------------------------------------------------------------------
unsigned char addr = 0x90; // Temperature sensor device Address
char str[12];
int tempr;
//------------------------------------------------------------------------------
int main() 
{	      
  ht16k33_init();
	mcp9800_init(addr, RES12_BIT); 

  while(1)
  { 
    tempr = mcp9800_read(addr, TEMP_REG);
		
		sprintf(str, "%7.3f°%c", toFloat(tempr), (tempMode == 0) ? 'c' : 'f');
    ht16k33_displayNumText(str);
		__delay_ms(100);
  }
}
//------------------------------------------------------------------------------