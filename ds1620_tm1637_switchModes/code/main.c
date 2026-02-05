#include<reg52.h>
#include <stdio.h>
#include <ctype.h>
#include <./assets/delay/delay.h>
#include <./assets/Ext_Intr/Ext_Intr.h>
#include <./assets/ds1620/ds1620.h>
#include <./assets/TM1637/TM1637.h>
//------------------------------------------------------------------------------
float num, tempF;
char str[15];
//------------------------------------------------------------------------------
int main(void) 
{	     
  TM1637_init(7);
	ds1620_init(25, 20); // //Set thermostat high and low values
	ExtInt0_init();
  
  while(1)
  { 
		num = ds1620_getTempFloat();
		tempF = (tempMode == 0) ? num : (num * 9/5) + 32;
		
		sprintf(str, "%5.1f°%c", tempF, (tempMode == 0) ? 'c' : 'f');
		TM1637_displayText(str);
		
		__delay_ms(200);
  }
}
//------------------------------------------------------------------------------
