#include<reg52.h>
#include <./assets/TC72/TC72.h>
#include <./assets/MAX7219/MAX7219.h>
//------------------------------------------------------------------------------
int main() 
{	  
  signed int tempr;	
  MAX7219_init();
  TC72_Init();

  while(1)
  { 
	  tempr = TC72_ReadTempr();
		
		tempr = toFloat(tempr) * 10;
    MAX7219_displayNumber(tempr);
  }
}
//------------------------------------------------------------------------------