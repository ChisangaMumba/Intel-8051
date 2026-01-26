#ifndef MCP320X_PROTOTYPES_H
#define	MCP320X_PROTOTYPES_H
//------------------------------------------------------------------------------
#include "../Soft_SPI/Soft_SPI.h"
//------------------------------------------------------------------------------
#define		DIFFERENTIAL_MODE		0x04
#define		SINGLE_MODE	        0x06
//------------------------------------------------------------------------------
void			mcp320x_init(void);
uint16_t	mcp320x_read(uint8_t mode, uint8_t chn);
float 		mcp320x_getVoltage(uint8_t mode, uint8_t chn);
float 		calcVoltage(uint16_t adcValue);
//------------------------------------------------------------------------------
uint8_t channel[8] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 };
//------------------------------------------------------------------------------
#endif