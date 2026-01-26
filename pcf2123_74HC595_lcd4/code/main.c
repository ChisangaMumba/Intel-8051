#include<reg52.h>
#include <stdio.h>
#include <./assets/pcf2123/pcf2123.h>
#include <./assets/Lcd/LCD_Serial.h>
//------------------------------------------------------------------------------
char str[30];  
int time[7] = {0,10,16,2,4,5,20}; //Sec,Min,Hour,WDay,MDay,Month,Year
//------------------------------------------------------------------------------
int main() 
{	
	LCD_init();
	PCF2123_init();
  
  PCF2123_setDateTime(time);
	
  while(1)
  { 
		PCF2123_getDateTime(time);
    
		sprintf(str,"Time:%s",get_fullTimeStr(time));      //Time
		LCD_string(0,0,str);
   
		sprintf(str,"Date:%s, %s",get_wDayStr(time[4]), get_fullDateStr(time));      //Date
		LCD_string(1,0,str);
  }
}
//------------------------------------------------------------------------------