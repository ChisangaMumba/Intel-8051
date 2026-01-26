#include<reg52.h>
#include <stdio.h>
#include <string.h>
#include "assets/Ext_Intr/Ext_Intr.h"
#include <./assets/ds1307/ds1307.h>
#include <./assets/ht16k33/ht16k33.h>
//------------------------------------------------------------------------------
char str[12];
int time[8];
//------------------------------------------------------------------------------
int main() 
{	      
  ht16k33_init();
  ds1307_init();
	ExtInt0_init();

  while(1)
  { 
    ds1307_getDateTime(time);
		
		if(LED0)
			strcpy(str, get_TimeStr(time));
		else
				if(LED1)
						strcpy(str, get_DateStr(time));
   
    ht16k33_displayNumText(str);
		__delay_ms(1000);
  }
}
//------------------------------------------------------------------------------