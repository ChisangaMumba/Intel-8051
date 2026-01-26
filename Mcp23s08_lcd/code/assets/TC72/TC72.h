#ifndef TC72_H
#define	TC72_H
//------------------------------------------------------------------------------
#include "../soft_SPI/soft_SPI.h"
#include "./assets/delay/delay.h"
//------------------------------------------------------------------------------
#define CONTROL_REG   0x80
#define START_CONV    0x10
#define TEMPR_REG     0x02
#define FRAC_FLAG     0x00C0
#define DEG_SYMBOL		0xDF    //223 (0xDF) is ° symbol. Not a standard ascii character
//------------------------------------------------------------------------------
void TC72_Init()
{
  CS2 = 1;
  
  SPI_write(CONTROL_REG);
  SPI_write(START_CONV);       //Continous conversion
  
  CS2 = 0;
  __delay_ms(150);
}
//------------------------------------------------------------------------------
int TC72_ReadTempr()
{ 
  char temprMSB, temprLSB; 
    
  CS2 = 1;
  
  SPI_write(TEMPR_REG);                  //Access Tempr register for reading
  temprMSB = SPI_read();     
  temprLSB = SPI_read();
  
  CS2 = 0;
  
  return ((temprMSB<<8) + temprLSB);
}
//------------------------------------------------------------------------------
float toFloat(signed int tempr)
{
  float result = (float)(tempr>>8);      //Discard LSByte (Only holds fraction flag bits)
  int count = tempr & FRAC_FLAG;          
  
  if(count) 
  {
    count = count >> 6; 
    result = result + (float)(count * 0.25);
  }
  
  return  (result);
}
//------------------------------------------------------------------------------
#endif

