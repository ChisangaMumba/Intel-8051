#include<reg52.h>
#include <stdio.h>
#include <stdlib.h>
#include "assets/Ext_Intr/Ext_Intr.h"
#include <./assets/pcf2123/pcf2123.h>
#include <./assets/MAX7219/MAX7219.h>
//------------------------------------------------------------------------------
char str[10];  
int time[7]; //Sec,Min,Hour,WDay,MDay,Month,Year
//------------------------------------------------------------------------------
int main() 
{	  
  MAX7219_init(SCAN_ALL_DIGITS);
	PCF2123_init();
	ExtInt0_init();
  //PCF2123_setDateTime(time);   //Uncomment to set time as needed
      
  while(1)
  { 
	  PCF2123_getDateTime(time);
	
		if(LED0)
			strcpy(str, get_TimeStr(time));
		else
				if(LED1)
					strcpy(str, get_DateStr(time));
		
		MAX7219_displayNumText(str);	
  }
}
//------------------------------------------------------------------------------