#ifndef MCP9800_H
#define	MCP9800_H
//------------------------------------------------------------------------------
#include <./assets/delay/delay.h>
#include <./assets/i2c/i2c.h>
#include "assets/Ext_Intr/Ext_Intr.h"
#include "mcp9800_Prototypes.h"
//------------------------------------------------------------------------------
void mcp9800_init(unsigned char addr, unsigned char res)
{
  ExtInt0_init();
	__delay_ms(10);
	mcp9800_writeConfig(addr, res);
}
//------------------------------------------------------------------------------
void mcp9800_writeConfig(unsigned char addr, unsigned char settings)
{
	I2C_start(); 
    
  I2C_write( addr + Wr ); 
  I2C_write( CONFIG_REG ); 
  I2C_write( settings );       
                           
  I2C_stop();
}
//------------------------------------------------------------------------------
unsigned char mcp9800_readConfig(unsigned char addr)
{
	 unsigned char config = 0;
	
   I2C_start();
    
   I2C_write( addr + Wr );
	 I2C_write( CONFIG_REG );
	 I2C_restart();	
   I2C_write( addr + Rd );	        
   config = I2C_read(NACK);    // Signal End of reception with NACK
	
   I2C_stop(); 
	
	 return config;
}
//------------------------------------------------------------------------------
void mcp9800_write(unsigned char addr, unsigned char reg, unsigned int settings)
{
	I2C_start(); 
    
  I2C_write( addr + Wr ); 
  I2C_write( reg ); 
  I2C_write( settings >> 8);
	I2C_write( settings & 0x00ff);
                           
  I2C_stop();
}
//------------------------------------------------------------------------------
int mcp9800_read(unsigned char addr, unsigned char reg)
{
	 unsigned char _data[2];
   
   I2C_start(); 	           
   	
   I2C_write( addr + Wr );	    
   I2C_write( reg );	    
   I2C_restart();	
   I2C_write( addr + Rd );	    
   _data[1] = I2C_read(ACK);     
   _data[0] = I2C_read(NACK);    // Signal End of reception with NACK
	
   I2C_stop();	
   
   return ( (_data[1] << 8) + _data[0] );   //NB: Result is 16bits Long
}
//------------------------------------------------------------------------------
float toFloat(signed int tempr)
{
	float result = (tempr >> 8);     
  int count = tempr & 0x00F0;          
  
  if(count) 
  {
    result += ((count>>4) * 0.0625);  
  }
  
  return (tempMode == 0) ? result : (result * 9/5) + 32;   // °C or °F;
}
//------------------------------------------------------------------------------
#endif