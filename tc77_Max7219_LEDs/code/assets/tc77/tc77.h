#ifndef TC77_H
#define TC77_H
//------------------------------------------------------------------------------
#include "./assets/delay/delay.h"
#include "assets/Ext_Intr/Ext_Intr.h"
#include "tc77_prototypes.h"
#include <./assets/soft_SPI/soft_SPI.h>
//------------------------------------------------------------------------------
void TC77_init()
{
  SPI_init();
	ExtInt0_init();
  __delay_ms(300);
}
//------------------------------------------------------------------------------
signed int TC77_read()
{   
  unsigned char data_[2];  
  
  CS2 = 0;
  
  data_[1] = SPI_read();     
  data_[0] = SPI_read();
  
  CS2 = 1;
  
	return (data_[1]<<8) + data_[0];
}
//------------------------------------------------------------------------------
float toFloat(signed int tempr)
{
  float result = (tempr >> 7);     
  char count = tempr & FRAC_FLAG;          
  
  if(count) 
  {
    count = count >> 3; 
    result = result + (count * 0.0625);  
  }
  
  return (tempMode == 0) ? result : (result * 9/5) + 32;   // °C or °F;
}
//------------------------------------------------------------------------------
#endif 