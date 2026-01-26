#include<reg52.h>
#include <stdio.h>
#include <./assets/lm75/LM75.h>
#include <./assets/ht16k33/ht16k33.h>
//------------------------------------------------------------------------------
int main() 
{	      
  ht16k33_init();
  LM75_init();

  while(1)
  { 
    signed int tempr = (signed int) (LM75_read(TEMPERATURE_ADDRESS) * 10);
   
    ht16k33_displayNum(tempr);
  }
}
//------------------------------------------------------------------------------