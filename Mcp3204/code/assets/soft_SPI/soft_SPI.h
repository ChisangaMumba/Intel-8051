#ifndef SPI_H
#define	SPI_H
//------------------------------------------------------------------------------
#include "soft_SPI_Pins.h"
//------------------------------------------------------------------------------
void SPI_init(void)
{
  SCLK = 0;
  SDOUT = 0;
  SDIN = 1;
}
//--------------------------TX: transmit _data-----------------------------------
void SPI_write(uint8_t send)
{	
	uint8_t tx;
	
	for(tx = 0; tx < 8; tx++)
	{
		SCLK = 0;
		SDOUT = ((send << tx) & 0x80) ? 1 : 0;
		SCLK = 1;
	}
}
//--------------------------RX: recieve _data------------------------------------
uint8_t SPI_read(void)
{
  uint8_t rx, data_ = 0;
	
  for(rx = 0 ; rx < 8 ; rx++)
  {
    SCLK = 0;
		if(SDIN) data_ += (0x01 << (7-rx));  //MSB first.
		SCLK = 1;
  }

  return data_;
}
//------------------------------------------------------------------------------
#endif