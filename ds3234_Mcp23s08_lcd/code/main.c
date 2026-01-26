#include<reg52.h>
#include <stdio.h>
#include <stdlib.h>
#include "assets/ds3234/ds3234_RTC.h"
#include "assets/lcd/LCD_Serial.h"
//------------------------------------------------------------------------------
char str[30];  
int tm[7] = {0,10,16,2,4,5,20}; //Sec,Min,Hour,WDay,MDay,Month,Year
//------------------------------------------------------------------------------
int main() 
{
  LCD_init();  
	DS3234_init();
	//DS3234_setTime(tm);       //Uncomment to set time as needed
	
  while(1)
  {
		DS3234_getTime(tm);
    
		sprintf(str,"Time:%s",get_fullTimeStr(tm));      //Time
		LCD_string(0,0,str);
   
		sprintf(str,"Date:%s, %s",get_wDayStr(tm[3]), get_fullDateStr(tm));      //Date
		LCD_string(1,0,str);
  }
}
//------------------------------------------------------------------------------