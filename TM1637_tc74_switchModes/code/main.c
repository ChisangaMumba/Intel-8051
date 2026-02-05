#include<reg52.h>
#include <./assets/tc74/tc74.h>
#include <./assets/TM1637/TM1637.h>
//------------------------------------------------------------------------------
char str[10];
signed int tempr = 0;
//------------------------------------------------------------------------------
int main() 
{	     
  TM1637_init(7);
	TC74_init(NORMAL_MODE);						// NORMAL vs STANDBY mode;
  
  while(1)
  {      
		tempr = TC74_read(TEMPR_REG) * 10;

		sprintf(str, "%4i°%c", tempr, (tempMode == 0) ? 'c' : 'f');
		TM1637_displayText(str);
		__delay_ms(200);
  }
}
//------------------------------------------------------------------------------
