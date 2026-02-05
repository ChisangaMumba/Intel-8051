#ifndef MCP9800_H
#define	MCP9800_H
//------------------------------------------------------------------------------
#include "mcp9800_Prototypes.h"
//------------------------------------------------------------------------------
void mcp9800_init(unsigned char addr, unsigned char res)
{
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
unsigned char mcp9800_getResolutionNum(unsigned char addr)
{
  unsigned char resNum = mcp9800_readConfig(addr);
  
	return (resNum & 0x60) >> 5;
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
	 unsigned char data_[2];
   
   I2C_start(); 	           
   	
   I2C_write( addr + Wr );	    
   I2C_write( reg );	    
   I2C_restart();	
   I2C_write( addr + Rd );	    
   data_[1] = I2C_read(ACK);     
   data_[0] = I2C_read(NACK);    // Signal End of reception with NACK
	
   I2C_stop();	
   
   return ( (data_[1] << 8) + data_[0] );   //NB: Result is 16bits Long
}
//------------------------------------------------------------------------------
float calcTemp(signed int rawData, unsigned char resInd)
{
	float tempr = (rawData >> 8);     
  int count = rawData & 0x00F0;          
  
  if(count) 
  {
		tempr += ((count >> (7-resInd)) * resValues[resInd]);
  }
  
  return tempr;
}
//------------------------------------------------------------------------------
#endif