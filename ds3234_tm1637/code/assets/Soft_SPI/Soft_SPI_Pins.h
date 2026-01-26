#ifndef SPI_PINS_H
#define	SPI_PINS_H
//------------------------------------------------------------------------------
sbit SCLK  = P1^2;         //Serial Clock
sbit SDOUT = P1^0;         //Serial Data Out
sbit SDIN  = P1^1;         //Serial Data In
sbit CS   = P1^3;         //Chip Select
//------------------------------------------------------------------------------
#endif