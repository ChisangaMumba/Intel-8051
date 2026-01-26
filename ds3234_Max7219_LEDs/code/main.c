#include<reg52.h>
#include <stdio.h>
#include <stdlib.h>
#include "assets/Ext_Intr/Ext_Intr.h"
#include "assets/ds3234/ds3234_RTC.h"
#include <./assets/MAX7219/MAX7219.h>
//------------------------------------------------------------------------------
char str[10];  
int tm[7]; //Sec,Min,Hour,WDay,MDay,Month,Year
//------------------------------------------------------------------------------
int main() 
{	  
  MAX7219_init(SCAN_ALL_DIGITS);
  DS3234_init();
	ExtInt0_init();
	//DS3234_setTime(tm);       //Uncomment to set time as needed

  while(1)
  { 
	  DS3234_getTime(tm);
	
		if(LED0)
			sprintf(str, "%02d%02d%02d", tm[2], tm[1], tm[0]);        //Time
		else
				if(LED1)
						sprintf(str, "%02d%02d%02d", tm[4], tm[5], tm[6]);  //Date
		
		MAX7219_displayNumText(str);	
  }
}
//------------------------------------------------------------------------------