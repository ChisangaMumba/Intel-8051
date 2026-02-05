#include<reg52.h>
#include <./assets/TC72/TC72.h>
#include <./assets/MAX7219/MAX7219.h>
//------------------------------------------------------------------------------
signed int tempr;
char str[10];
//------------------------------------------------------------------------------
int main() 
{	  
  MAX7219_init(4);     //Number of chips
  TC72_init();

  while(1)
  { 
	  tempr = TC72_readTempr();
		
		sprintf(str, "%5.1f", toFloat(tempr));
		MAX7219_displayText(str);
  }
}
//------------------------------------------------------------------------------