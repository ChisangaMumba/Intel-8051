#include<reg52.h>
#include <stdio.h>
#include <stdlib.h>
#include <./assets/TC72/TC72.h>
#include <./assets/Max6951/Max6951.h>
//------------------------------------------------------------------------------
char str[8]; 
signed int tempr;
//------------------------------------------------------------------------------
int main() 
{	  
  MAX6951_init();;
  TC72_Init(); 
	
  while(1)
  { 	
		tempr = TC72_ReadTempr();
		sprintf(str, "%7.2f°%c", toFloat(tempr), (tempMode == 0) ? 'c' : 'f');  
		MAX6951_displayText(str);
  }
}
//------------------------------------------------------------------------------