#ifndef EXPANDER_H
#define EXPANDER_H
//------------------------------------------------------------------------------
#include "MCP23008_Prototypes.h"
#include <./assets/i2c/i2c.h>
//------------------------------------------------------------------------------
void EXPANDER_init(char _data)
{
  I2C_init();          
  
  EXPANDER_write(IODIR, _data);
}
//------------------------------------------------------------------------------
void EXPANDER_write(char regAddress, char _data)
{
  I2C_start();
  I2C_write(WRITE);
  I2C_write(regAddress);
  I2C_write(_data);
  I2C_stop();
}
//------------------------------------------------------------------------------
char EXPANDER_read()
{
	char _data;
	
  I2C_start();
  
  I2C_write(WRITE);
  I2C_write(OLAT);
  I2C_restart();
  I2C_write(READ);
  _data = I2C_read(1);
  
  I2C_stop();

  return _data;
}
//------------------------------------------------------------------------------
#endif