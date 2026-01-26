#ifndef DS1621_H
#define	DS1621_H
//------------------------------------------------------------------------------
#include "ds1621_Prototypes.h"
#include <./assets/i2c/i2c.h>
//------------------------------------------------------------------------------
void ds1621_init(unsigned char addr)
{
  ds1621_config(addr);
	ds1621_convertCmd(addr, START_CONV);
}
//----------------------------Setup Device--------------------------------------
void ds1621_config(unsigned char addr)
{
  I2C_start(); 
    
  I2C_write( addr + Wr ); 
  I2C_write( CONFIG_REG ); 
  I2C_write( CONT_CONV );       // Continuous conversion, Active high polarity
                           
  I2C_stop();
}
//--------------------Start or stop tempr converstion---------------------------
void ds1621_convertCmd(unsigned char addr, unsigned char command)
{
   I2C_start();
    
   I2C_write( addr + Wr );
   I2C_write( command );
	
   I2C_stop(); 
}
//------------------------------------------------------------------------------
unsigned char ds1621_read1ByteReg(unsigned char addr, unsigned char deviceReg)
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
void ds1621_write2ByteReg(unsigned char addr, unsigned char deviceReg, unsigned int settings)
{   
   I2C_start(); 	           
   	
   I2C_write( addr + Wr );	    
   I2C_write( deviceReg );	    
	 I2C_write( settings >> 8);
	 I2C_write( settings & 0x00ff);
                           
   I2C_stop();
}
//------------------------------------------------------------------------------
int ds1621_read2ByteReg(unsigned char addr, unsigned char deviceReg)
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
float toFloat(signed int tempr)
{
  float result = tempr >> 8;     //Get rid of lower 8 bits (Only contains Fraction bit)

  return (tempr & FRAC_FLAG) ? result + 0.5 : result;
}
//------------------------------------------------------------------------------
#endif