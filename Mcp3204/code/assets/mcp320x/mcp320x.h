#ifndef MCP320X_H
#define	MCP320X_H
//------------------------------------------------------------------------------
#include "mcp320x_prototypes.h"
sbit CS2 = P1^4;         // Chip Select 2
//------------------------------------------------------------------------------
void mcp320x_init(void)
{
	SPI_init();
	
	CS2 = 1; // deselect initially
}
//-----------------------------Returns 0..4095----------------------------------
uint16_t mcp320x_read(uint8_t mode, uint8_t chn)
{
	uint8_t data_[2];
	uint16_t cmd = ((mode << 8) | (channel[chn] << 6));
		
  CS2 = 0;                     
 
	SPI_write(cmd >> 4);   
	data_[1] = SPI_read();		// MSB
  data_[0] = SPI_read();		// LSB
  
  CS2 = 1;
  
	return ((data_[1] << 4) | (data_[0] >> 4));
}
//------------------------------------------------------------------------------
float mcp320x_getVoltage(uint8_t mode, uint8_t chn)
{
	uint16_t rawData = mcp320x_read(mode, chn);
	
	return calcVoltage(rawData);
}
//------------------------------------------------------------------------------
float calcVoltage(uint16_t adcValue)
{
	float Vin = (float)(adcValue * 5)/4096; //Vin = (Code * Vref)/4096. See MCP3204 datasheet page 17
	
	return Vin;
}
//------------------------------------------------------------------------------
#endif