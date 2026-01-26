#ifndef SPI_H
#define	SPI_H
//------------------------------------------------------------------------------
#include "Soft_SPI_Pins.h"
//------------------------------------------------------------------------------
void SPI_init(void)
{
  SCLK = 0;
  SDOUT = 0;
  SDIN = 1;
  CS1  = 0;
	CS2  = 0;
}
//--------------------------TX: transmit _data-----------------------------------
void SPI_write(unsigned char send)
{	
	unsigned char tx;
	for(tx = 0; tx < 8; tx++)
	{
		SCLK = 0;
		SDOUT = ((send << tx) & 0x80) ? 1 : 0;
		SCLK = 1;
	}
}
//--------------------------RX: recieve _data------------------------------------
unsigned char SPI_read(void)
{
  unsigned char rx, bitVal, _data = 0;
  for(rx = 0 ; rx < 8 ; rx++)
  {
    SCLK = 0;
		bitVal = SDIN;
    _data += (bitVal << (7-rx));  //MSB first.
		SCLK = 1;
  }

  return _data;
}
//------------------------------------------------------------------------------
#endif