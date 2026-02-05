#ifndef TC72_H
#define	TC72_H
//------------------------------------------------------------------------------
#include "./assets/delay/delay.h"
#include "../soft_SPI/soft_SPI.h"
//------------------------------------------------------------------------------
#define CONTROL_REG   0x80
#define START_CONV    0x10
#define TEMPR_REG     0x02
#define FRAC_FLAG     0x00C0
#define DEG_SYMBOL		0xDF			//223 (0xDF) is ° symbol. Not a standard ascii character
//------------------------------------------------------------------------------
void TC72_Init()
{
  CS2 = 0;		//Deselect initially
	
  CS2 = 1;
  
  SPI_write(CONTROL_REG);
  SPI_write(START_CONV);				//Continous conversion
  
  CS2 = 0;
  __delay_ms(150);
}
//------------------------------------------------------------------------------
int TC72_ReadTempr()
{ 
  unsigned char tempr[2];	
	
  CS2 = 1;
  
  SPI_write(TEMPR_REG);                  //Access Tempr _register for reading
  tempr[1] = SPI_read();  	                  
	tempr[0] = SPI_read();
  
  CS2 = 0;
  
  return ((tempr[1] << 8) + tempr[0]);
}
//------------------------------------------------------------------------------
float toFloat(signed int tempr)
{
  float result = (float)(tempr >> 8);      //Discard LSByte (Only holds fraction flag bits)
  int count = tempr & FRAC_FLAG;          
  
  if(count) 
  {
    result += ((count >> 6) * 0.25);
  }
  
  return  (result);
}
//------------------------------------------------------------------------------
#endif