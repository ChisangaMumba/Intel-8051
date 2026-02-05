#ifndef TC72_H
#define	TC72_H
//------------------------------------------------------------------------------
#include "./assets/TC72/TC72_prototypes.h"
//------------------------------------------------------------------------------
void TC72_init()
{
  CS2 = 1;
  
  SPI_write(CONTROL_REG);
  SPI_write(START_CONV);       //Continous conversion
  
  CS2 = 0;
  __delay_ms(150);
}
//------------------------------------------------------------------------------
int TC72_readTempr()
{ 
  unsigned char tempr[2]; 
    
  CS2 = 1;
  
  SPI_write(TEMPR_REG);                  //Access Tempr register for reading
  tempr[1] = SPI_read();     
  tempr[0] = SPI_read();
  
  CS2 = 0;
  
  return ((tempr[1] << 8) + tempr[0]);
}
//------------------------------------------------------------------------------
float toFloat(signed int tempr)
{  
  return (tempr / pow(2,8));
}
//------------------------------------------------------------------------------
#endif

