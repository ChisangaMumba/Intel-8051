#ifndef DS1621_H
#define	DS1621_H
//------------------------------------------------------------------------------
#include <./assets/i2c/i2c.h>
#include <assets/Ext_Intr/Ext_Intr.h>
#include "ds1621_Prototypes.h"
//------------------------------------------------------------------------------
void ds1621_init(unsigned char Addr)
{
	ExtInt0_init();
  ds1621_config(Addr);
  ds1621_startConv(Addr);
}
//----------------------------Setup Device--------------------------------------
void ds1621_config(unsigned char Addr)
{
  I2C_start(); 
    
  I2C_write( Addr + Wr ); 
  I2C_write( CONFIG_REG ); 
  I2C_write( CONT_CONV );       // Continuous conversion,Active high polarity
                           
  I2C_stop();
}
//------------------------Start tempr converstion--------------------------------
void ds1621_startConv(unsigned char Addr)
{
   I2C_start();
    
   I2C_write( Addr + Wr );
   I2C_write( START_CONV );
	
   I2C_stop(); 
}
//------------------------------------------------------------------------------
int ds1621_readTemp(unsigned char Addr)
{
   unsigned char tempHi,tempLo;
   
   I2C_start(); 	           
   	
   I2C_write( Addr + Wr );	    
   I2C_write( TEMP_REG );	    // Access the temperature register
   I2C_restart();	           
   I2C_write( Addr + Rd );	    
   tempHi = I2C_read(ACK);     
   tempLo = I2C_read(NACK);    // Signal End of reception with NACK
	
   I2C_stop();	
   
   return ((tempHi << 8) + tempLo);   //NB: Result is 16bits Long
}
//------------------------------------------------------------------------------
float toFloat(signed int tempr)
{
  float newTempr = (float)(tempr >> 8);     //Get rid of lower 8 bits (Only contains Fraction bit)

	if(tempr & FRAC_FLAG)
	{
		newTempr += 0.5;
	}
	
	return (tempMode == 0) ? newTempr : (newTempr * (float)9/5) + 32; // C or F
}
//------------------------------------------------------------------------------
#endif