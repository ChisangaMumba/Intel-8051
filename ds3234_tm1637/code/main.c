#include<reg52.h>
#include <stdio.h>
#include <string.h>
#include "assets/Ext_Intr/Ext_Intr.h"
#include <./assets/ds3234/ds3234.h>
#include <./assets/TM1637/TM1637.h>
//------------------------------------------------------------------------------
char str[12];
int time[8];
//------------------------------------------------------------------------------
int main() 
{	     
  TM1637_init(7);
	ExtInt0_init();
	DS3234_init();
	//DS3234_setTime(tm);       //Uncomment to set time as needed
  
  while(1)
  {      
		DS3234_getTime(time);
		
		if(LED0)
			strcpy(str, get_TimeStr(time));
		else
				if(LED1)
					strcpy(str, get_DateStr(time));
				
		TM1637_displayNumText(str);
		__delay_ms(200);
  }
}
//------------------------------------------------------------------------------
