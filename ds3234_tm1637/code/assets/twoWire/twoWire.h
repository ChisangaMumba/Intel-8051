#ifndef  TWO_WIRE_H
#define  TWO_WIRE_H
//------------------------------------------------------------------------------
#include <./assets/delay/delay.h>
//NB: Very similar to i2c but NOT entirely 
//------------------------------------------------------------------------------
sbit SCK = P0^0;
sbit SDA = P0^1;
//------------------------------------------------------------------------------
void twoWire_init()
{  
  SCK = 0;
  SDA = 0;
}
//------------------------------------------------------------------------------
void twoWire_start()
{
  SCK = 1;
  SDA = 1;
  __delay_us(2);
  SDA = 0;
}
//------------------------------------------------------------------------------
void twoWire_stop()
{
  SCK = 0;
  __delay_us(2);
  SDA = 0;
  __delay_us(2);
  SCK = 1;
  __delay_us(2);
  SDA = 1;
}
//------------------------------------------------------------------------------
void twoWire_ack()
{
  SCK = 0;
  __delay_us(5);
  SCK = 1;
  __delay_us(2);
  SCK = 0;
}
//------------------------------------------------------------------------------
void twoWire_write(char _data)
{
	char tx;
	
  for(tx = 0 ; tx < 8 ; tx++)
  {
    SCK = 0;
    SDA = ((_data >> tx) & 0x01) ? 1 : 0 ; 	//LSB first (Real 12c sends MSB first)
    SCK = 1;                              	//Toggle SCK pin to latch data bit
    
    __delay_us(6);
  }
}
//------------------------------------------------------------------------------
#endif  /* TWO_WIRE_H */