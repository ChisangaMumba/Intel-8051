#include<reg52.h>
#include <./assets/ds1621/ds1621.h>
#include <./assets/TM1637/TM1637.h>
//------------------------------------------------------------------------------
unsigned char addr = 0x90; // Temperature sensor device Address
float tempr;
char str[10];
//------------------------------------------------------------------------------
int main() 
{	     
  TM1637_init(7);
	ds1621_init(addr);
	  
  while(1)
  { 
		tempr = ds1621_readTemp(addr);
		sprintf(str, "%5.1f°%c", toFloat(tempr), (tempMode == 0) ? 'c' : 'f');
		
		TM1637_displayText(str);
		__delay_ms(100);
  }
}
//------------------------------------------------------------------------------
