#include<reg52.h>
#include <stdio.h>
#include <stdlib.h>
#include <./assets/TC72/TC72.h>
#include <./assets/Max6950/Max6950.h>
//------------------------------------------------------------------------------
char str[8]; 
signed int tempr;
//------------------------------------------------------------------------------
int main() 
{	  
  MAX6950_init();;
  TC72_Init(); 
	
  while(1)
  { 	
		tempr = TC72_ReadTempr();
		MAX6950_displayNumber(toFloat(tempr));
  }
}
//------------------------------------------------------------------------------