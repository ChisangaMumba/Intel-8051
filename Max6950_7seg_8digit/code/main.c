#include<reg52.h>
#include <stdio.h>
#include <stdlib.h>
#include <./assets/TC72/TC72.h>
#include <./assets/Max6950/Max6950.h>
//------------------------------------------------------------------------------
char str[15]; 
signed int tempr;
//------------------------------------------------------------------------------
int main() 
{	  
  MAX6950_init(2);
  TC72_Init(); 
	
  while(1)
  { 	
		tempr = TC72_ReadTempr();
		sprintf(str, "%7.2f°c", toFloat(tempr));
		
		MAX6950_displayText(str);
  }
}
//------------------------------------------------------------------------------