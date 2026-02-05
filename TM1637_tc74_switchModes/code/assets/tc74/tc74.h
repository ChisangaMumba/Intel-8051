#ifndef TC74_H
#define	TC74_H
//------------------------------------------------------------------------------
#include <./assets/i2c/i2c.h>
#include "assets/Ext_Intr/Ext_Intr.h"
#include "TC74_Prototypes.h"
//------------------------------------------------------------------------------
void TC74_init(char _data)
{
  I2C_init();
	ExtInt0_init();
	TC74_config(_data);
}
//------------------------------------------------------------------------------
void TC74_config(char _data)
{
  I2C_start();                      
  
  I2C_write(READ);								//Datasheet says WRITE (0x9B), but that does NOT work              
  I2C_write(CONFIG_REG);                                      
  I2C_write(_data);                
  
  I2C_stop();
}
//------------------------------------------------------------------------------
signed char TC74_read(char regAddress)
{
	signed char result = 0;
	
  I2C_start();                      
  
  I2C_write(READ);								//Datasheet says WRITE (0x9B), but that does NOT work 
  I2C_write(regAddress);           
  I2C_restart();                           
  I2C_write(WRITE);								//Datasheet says READ (0x9A), but that does NOT work                 
	result = (signed char) I2C_read(NACK);
  
  I2C_stop();
  
  return (tempMode == 0) ? result : (result * 9/5) + 32;   // °C or °F
}
//------------------------------------------------------------------------------
#endif