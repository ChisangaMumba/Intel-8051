#ifndef DS1631_H
#define	DS1631_H
//------------------------------------------------------------------------------
#include <./assets/delay/delay.h>
#include "ds1631_Prototypes.h"
#include <./assets/i2c/i2c.h>
#include <math.h>
//------------------------------------------------------------------------------
void ds1631_init(unsigned char addr,unsigned char resolution)
{	
	ds1631_config(addr, 0);
	__delay_ms(12);			//10ms delay is required between consecutive writes to config reg
	ds1631_config(addr, resolution);
	ds1631_convertCmd(addr, START_CONV);
	__delay_ms(750);    //12 _bit resolution requires 750ms conversion time, see datasheet
}
//----------------------------Setup Device--------------------------------------
void ds1631_config(unsigned char addr, unsigned char command)
{
  I2C_start(); 
    
  I2C_write( addr + Wr ); 
  I2C_write( CONFIG_REG ); 
  I2C_write( command );       // Continuous conversion, Active high polarity
                           
  I2C_stop();
}
//--------------------Start or stop tempr converstion---------------------------
void ds1631_convertCmd(unsigned char addr, unsigned char command)
{
   I2C_start();
    
   I2C_write( addr + Wr );
   I2C_write( command );
	
   I2C_stop(); 
}
//------------------------------------------------------------------------------
unsigned char ds1631_read1ByteReg(unsigned char addr, unsigned char deviceReg)
{
   unsigned char _data;
   
   I2C_start(); 	           
   	
   I2C_write( addr + Wr );	    
   I2C_write( deviceReg );	    
   I2C_restart();	           
   I2C_write( addr + Rd );	        
   _data = I2C_read(NACK);    // Signal End of reception with NACK
	
   I2C_stop();	
   
   return _data;  
}
//------------------------------------------------------------------------------
void ds1631_write2ByteReg(unsigned char addr, unsigned char deviceReg, unsigned int settings)
{   
   I2C_start(); 	           
   	
   I2C_write( addr + Wr );	    
   I2C_write( deviceReg );	    
	 I2C_write( settings >> 8);
	 I2C_write( settings & 0x00ff);
                           
   I2C_stop();
}
//------------------------------------------------------------------------------
int ds1631_read2ByteReg(unsigned char addr, unsigned char deviceReg)
{
   unsigned char _data[2];
   
   I2C_start(); 	           
   	
   I2C_write( addr + Wr );	    
   I2C_write( deviceReg );	    
   I2C_restart();	           
   I2C_write( addr + Rd );	    
   _data[1] = I2C_read(ACK);     
   _data[0] = I2C_read(NACK);    // Signal End of reception with NACK
	
   I2C_stop();	
   
   return ( (_data[1] << 8) + _data[0] );   //NB: Result is 16bits Long
}
//------------------------------------------------------------------------------
unsigned char ds1631_getResolutionNum(unsigned char addr)
{
  unsigned char resNum = ds1631_read1ByteReg(addr, CONFIG_REG);
  
	return (resNum & 0x0C) >> 2;
}
//------------------------------------------------------------------------------
float toFloat(signed int tempr, unsigned char resInd)
{
	float resValues[4] = { 0.5, 0.25, 0.125, 0.0625 }; // 2^(-1), 2^(-2), 2^(-3), 2^(-4)
	float result = (float)(tempr >> 8);     
  int count = tempr & FRAC_FLAG;          
  
  if(count) 
  {
		result += ((count >> (7-resInd)) * resValues[resInd]);
  }
  
  return result;
}
//------------------------------------------------------------------------------
#endif