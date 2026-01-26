#include<reg52.h>
#include <./assets/TC72/TC72.h>
#include <./assets/MAX7219/MAX7219.h>
//------------------------------------------------------------------------------
signed int tempr;
char out[30];
//------------------------------------------------------------------------------
int main() 
{	  
  MAX7219_init(5);     //Number of chips
  TC72_init();

  while(1)
  { 
	  tempr = TC72_readTempr();
		
		sprintf(out, "%.2f", toFloat(tempr));
    MAX7219_displayText(out);
  }
}
//------------------------------------------------------------------------------