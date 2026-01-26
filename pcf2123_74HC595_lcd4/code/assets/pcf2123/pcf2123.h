#ifndef PCF2123_H
#define	PCF2123_H
//------------------------------------------------------------------------------
#include "./assets/soft_spi/Soft_SPI.h"
#include "Time_functions.h"
#include "pcf2123_prototypes.h"
//------------------------------------------------------------------------------
void PCF2123_init()
{
  SPI_init();
}
//------------------------------------------------------------------------------
void PCF2123_setDateTime(int time[])
{
  CS2 = 1;
  
  SPI_write(WR+SEC_REG);    //Auto Increments after initial Write
  SPI_write(get_BCDTime(time[0]));          //Secs
  SPI_write(get_BCDTime(time[1]));          //Mins
  SPI_write(get_BCDTime(time[2]));          //Hrs
  SPI_write(get_BCDTime(time[3]));          //Month Day
  SPI_write(get_BCDTime(time[4]));          //Week Day
  SPI_write(get_BCDTime(time[5]));          //Month
  SPI_write(get_BCDTime(time[6]));          //Years
  
  CS2 = 0;
}
//------------------------------------------------------------------------------
void PCF2123_getDateTime(int time[])
{
  CS2 = 1;
  
  SPI_write(RD+SEC_REG);   //Auto Increments after initial Read
  time[0] = get_DecTime(SPI_read() & OS_FLAG);   //Secs (Discards OS Flag from Secs _register)
  time[1] = get_DecTime(SPI_read());             //Mins
  time[2] = get_DecTime(SPI_read());             //Hrs
  time[3] = get_DecTime(SPI_read());             //Month Day
  time[4] = get_DecTime(SPI_read());             //Week Day
  time[5] = get_DecTime(SPI_read());             //Month
  time[6] = get_DecTime(SPI_read());             //Years
  
  CS2 = 0;
}
//------------------------------------------------------------------------------
#endif