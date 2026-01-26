#ifndef DS1307_H
#define	DS1307_H
//------------------------------------------------------------------------------
#include <./assets/i2c/i2c.h>
#include "Time_functions.h"
#include "DS1307_Protoypes.h"
//------------------------------------------------------------------------------
void RTC_init(void)
{
  I2C_init();  
}
//------------------------------------------------------------------------------
int RTC_readReg(int addr)
{
	int _data = 0;
	
  I2C_start();

  I2C_write(WRITE_CMD);                    
  I2C_write(addr);
  I2C_restart();
  I2C_write(READ_CMD);                     
  _data = get_DecTime(I2C_read(NACK));

  I2C_stop();
	
	return _data;
}
//----------------secs,mins,hrs,wDay,mDay,months,years-------------------------
void RTC_getDateTime(int time[])
{
	int addr;
	
  for(addr = 0; addr < 7; addr++)
  {
		time[addr] = RTC_readReg(addr);
  }
}
//------------------------------------------------------------------------------
void RTC_setDateTime(int regAddr, int _data)
{
  I2C_start();

  I2C_write(WRITE_CMD);
  I2C_write(regAddr);
  I2C_write(_data);

  I2C_stop();
}
//------------------------------------------------------------------------------
#endif