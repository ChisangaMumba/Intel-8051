#include<reg52.h>
#include <stdio.h>
#include <stdlib.h>
#include <./assets/ds1307/ds1307.h>
#include <./assets/lcd/LCD_Serial.h>
//------------------------------------------------------------------------------
char str[20];
int time[8];
//------------------------------------------------------------------------------
int main() 
{
  LCD_init(0x4E);       // Expander Address  
	ds1307_init();
	
  while(1)
  {
		ds1307_getDateTime(time);
		
		sprintf(str, "%s, %s", get_wDayStr(time[3]), get_fullDateStr(time)); //Date
		LCD_string(0, 0, str);
		
		sprintf(str, "%s", get_fullTimeStr(time));      //Time
		LCD_string(1, 0, str);
  
		__delay_ms(1000);   
  }
}
//------------------------------------------------------------------------------