#ifndef EXPANDER_H
#define EXPANDER_H
//------------------------------------------------------------------------------
#include "MCP23017_Prototypes.h"
#include <./assets/i2c/i2c.h>
//------------------------------------------------------------------------------
void EXPANDER_init(char portA, char portB)
{
  I2C_init();          
  
  EXPANDER_write(IODIRA, portA);
  EXPANDER_write(IODIRB, portB);
}
//------------------------------------------------------------------------------
void EXPANDER_write(char portAddr, char _data)
{
  I2C_start();
  I2C_write(WRITE);
  I2C_write(portAddr);
  I2C_write(_data);
  I2C_stop();
}
//------------------------------------------------------------------------------
char EXPANDER_read(char portAddr)
{
	char _data;
	
  I2C_start();
  
  I2C_write(WRITE);
  I2C_write(portAddr);
  I2C_restart();
  I2C_write(READ);
  _data = I2C_read(1);
  
  I2C_stop();

  return _data;
}
//------------------------------------------------------------------------------
#endif