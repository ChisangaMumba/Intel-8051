#ifndef EXPANDER_H
#define EXPANDER_H
//------------------------------------------------------------------------------
#include "mcp23s08_Prototypes.h"
#include <./assets/soft_SPI/soft_SPI.h>
//------------------------------------------------------------------------------
void EXPANDER_init(char _data)
{
  SPI_init();          
  EXPANDER_write(IODIR, _data);
}
//------------------------------------------------------------------------------
void EXPANDER_write(char regAddress, char _data)
{
  CS1 = 0;              //Chip Select: active low
  SPI_write(WRITE);
	SPI_write(regAddress);
  SPI_write(_data);
  CS1 = 1;
}
//------------------------------------------------------------------------------
char EXPANDER_read()
{
	char _data = 0;
	
  CS1 = 0;
  SPI_write(READ);
  SPI_write(OLAT);
  _data = SPI_read();
  CS1 = 1;

  return _data;
}
//------------------------------------------------------------------------------
#endif