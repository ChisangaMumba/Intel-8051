#ifndef  TWO_WIRE_H
#define  TWO_WIRE_H
//------------------------------------------------------------------------------
#include <./assets/delay/delay.h>
//NB: Very similar to i2c but NOT entirely 
//------------------------------------------------------------------------------
sbit CLK = P0^0;
sbit DIO = P0^1;
//------------------------------------------------------------------------------
void twoWire_init()
{  
  CLK = 0;
  DIO = 0;
}
//------------------------------------------------------------------------------
void twoWire_start()
{
  CLK = 1;
  DIO = 1;
  __delay_us(2);
  DIO = 0;
}
//------------------------------------------------------------------------------
void twoWire_stop()
{
  CLK = 0;
  __delay_us(2);
  DIO = 0;
  __delay_us(2);
  CLK = 1;
  __delay_us(2);
  DIO = 1;
}
//------------------------------------------------------------------------------
void twoWire_ack()
{
  CLK = 0;
  __delay_us(5);
  CLK = 1;
  __delay_us(2);
  CLK = 0;
}
//------------------------------------------------------------------------------
void twoWire_write(char _data)
{
	char tx;
	
  for(tx = 0 ; tx < 8 ; tx++)
  {
    CLK = 0;
    DIO = ((_data >> tx) & 0x01) ? 1 : 0 ; 	//LSB first (Real 12c sends MSB first)
    CLK = 1;                              	//Toggle CLK pin to latch data bit
    
    __delay_us(6);
  }
}
//------------------------------------------------------------------------------
#endif  /* TWO_WIRE_H */