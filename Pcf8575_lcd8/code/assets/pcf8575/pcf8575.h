#ifndef PCF8575_EXPANDER_H
#define PCF8575_EXPANDER_H
//------------------------------------------------------------------------------
#include <./assets/i2c/i2c.h>
//------------------------------------------------------------------------------
void Expander_write(char portA, char portB);
char ADDRESS;                  
char PORT_A;
char PORT_B;
//------------------------------------------------------------------------------
void Expander_init(char addr)
{
  ADDRESS = addr;
  Expander_write(0x00,0x00);
}
//------------------------------------------------------------------------------
void Expander_write(char portA, char portB)
{
  I2C_start();
  
  I2C_write(ADDRESS);
  I2C_write(portA);
  I2C_write(portB);
  
  I2C_stop();
}
//------------------------------------------------------------------------------
void Expander_read()
{
  I2C_start();
  
  I2C_write(ADDRESS + 1);
  PORT_A = I2C_read(0);      //0 - ACK
  PORT_B = I2C_read(1);
  
  I2C_stop();
}
//------------------------------------------------------------------------------
#endif