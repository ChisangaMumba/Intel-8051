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
}
//--------------------------TX: transmit _data-----------------------------------
void SPI_write(signed char send)
{	
	char tx;
	for(tx = 0; tx < 8; tx++)
	{
		SCLK = 0;
		SDOUT = ((send << tx) & 0x80) ? 1 : 0;
		SCLK = 1;
	}
}
//--------------------------RX: recieve _data------------------------------------
char SPI_read(void)
{
  char Rx, bitVal, _data = 0;
  for(Rx = 0 ; Rx < 8 ; Rx++)
  {
    SCLK = 0;
		bitVal = SDIN;
    _data += (bitVal << (7-Rx));  //MSB first.
		SCLK = 1;
  }

  return _data;
}
//------------------------------------------------------------------------------
#endif