#include<reg52.h>
#include <stdio.h>
#include <stdlib.h>
#include "assets/lcd/LCD_Serial.h"
#include <./assets/ds1307/ds1307.h>
//------------------------------------------------------------------------------
char str[30];
int time[8];
//------------------------------------------------------------------------------
int main() 
{
  LCD_init();  
	RTC_init();
	
  while(1)
  {
		RTC_getDateTime(time);
		
		sprintf(str, "Time:%s", get_fullTimeStr(time));      //Time
		LCD_string(0, 0, str);
   
		sprintf(str, "Date:%s, %s", get_wDayStr(time[3]), get_fullDateStr(time)); //Date
		LCD_string(1, 0, str);
  }
}
//------------------------------------------------------------------------------