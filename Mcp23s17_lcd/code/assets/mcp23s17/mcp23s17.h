#ifndef EXPANDER_H
#define EXPANDER_H
//------------------------------------------------------------------------------
#include "mcp23s17_Prototypes.h"
#include <./assets/soft_SPI/soft_SPI.h>
//------------------------------------------------------------------------------
void EXPANDER_init(char portA, char portB)
{
  SPI_init();          //Initialize I2C bus with clock frequency of 100kHz
  EXPANDER_write(IODIRA,portA);
  EXPANDER_write(IODIRB,portB);
}
//------------------------------------------------------------------------------
void EXPANDER_write(char portAddr, char _data)
{
  CS1 = 0;              //Chip Select: active low
  SPI_write(WRITE);
  SPI_write(portAddr);
  SPI_write(_data);
  CS1 = 1;
}
//------------------------------------------------------------------------------
char EXPANDER_read(char portAddr)
{
	char _data = 0;
	
  CS1 = 0;
  SPI_write(READ);
  SPI_write(portAddr);
  _data = SPI_read();
  CS1 = 1;

  return _data;
}
//------------------------------------------------------------------------------
#endif