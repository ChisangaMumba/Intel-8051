#include<reg52.h>
#include <stdio.h>
#include <string.h>
#include <./assets/ds3234/ds3234.h>
#include <./assets/MAX7219/MAX7219.h>
//------------------------------------------------------------------------------
int time[7] = {0,59,16,2,4,5,20}; //Sec,Min,Hour,WDay,MDay,Month,Year
char str[20];
//------------------------------------------------------------------------------
int main() 
{	  
  MAX7219_init(4);     //Number of chips
  DS3234_init();
	//DS3234_setTime(tm);       //Uncomment to set time as needed

  while(1)
  { 
	  DS3234_getTime(time);
		strcpy(str, get_TimeStr(time));
		MAX7219_displayText(str);
  }
}
//------------------------------------------------------------------------------