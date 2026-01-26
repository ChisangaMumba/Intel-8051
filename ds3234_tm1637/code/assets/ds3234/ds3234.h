#ifndef DS3234_H
#define	DS3234_H
//------------------------------------------------------------------------------
#include "../soft_SPI/soft_SPI.h"
#include "Time_functions.h"
#include "ds3234_Prototypes.h"
//------------------------------------------------------------------------------
void DS3234_init()
{
  SPI_init();   
  CS = 1;      //Deselect initially
  
  DS3234_write(control_reg, 0x20);
  DS3234_write(status_reg, 0x48);
}
//------------------------------------------------------------------------------
int DS3234_read(int address)
{ 
	int value = 0;
	
  CS = 0;
  SPI_write(address + read_cmd);
  value = SPI_read(); 
  CS = 1;

  return value;
}
//------------------------------------------------------------------------------
void DS3234_write(int address,int value)
{
  unsigned long temp = 0;

  CS = 0;
  temp = (address + write_cmd);
  SPI_write(temp);
  SPI_write(value);
  CS = 1;
}
//------------------------------------------------------------------------------
void DS3234_setTime(int time[])
{
	int reg;
  
	for(reg = 0; reg < 7 ;reg++)
  {
    DS3234_write( reg , get_BCDTime(time[reg]) );//Sec,Min,Hour,WDay,MDay,Month,Year
  }
}
//------------------------------------------------------------------------------
void DS3234_getTime(int time[])
{
	int reg;
	
  for(reg = 0; reg < 7; reg++)
  {
    time[reg] = get_DecTime(DS3234_read(reg));//Sec,Min,Hour,WDay,MDay,Month,Year
  }
}
//------------------------------------------------------------------------------
#endif