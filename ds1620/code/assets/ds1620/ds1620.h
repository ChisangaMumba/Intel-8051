#ifndef DS1620_H
#define	DS1620_H
//------------------------------------------------------------------------------
#include "ds1620_prototypes.h"
//------------------------------------------------------------------------------
void ds1620_init(int tempH, int tempL)
{
	DQ = 0;                                       
	CLK = 0;       
	RST = 0;
	
	ds1620_writeConfig(0x0A);
	
	//Set thermostat high and low values (entirely optional)
	ds1620_writeT_HL(WRITE_TH, tempH);
	ds1620_writeT_HL(WRITE_TL, tempL);
	
	ds1620_convert(START_CONV);
}
//------------------------------------------------------------------------------
void ds1620_convert(char command)
{
	threeWire_start();
	threeWire_write(command, 8);
	threeWire_stop();
}
//------------------------------------------------------------------------------
int ds1620_read(char command)
{
	int data_ = 0;

	threeWire_start();
	threeWire_write(command, 8);
	data_ = threeWire_read();
	threeWire_stop();

	return data_;
}
//------------------------------------------------------------------------------
void ds1620_writeT_HL(char command, int data_)
{	
	threeWire_start();
	
	threeWire_write(command, 8);
	threeWire_write(data_ << 1, 16);
	__delay_ms(20);

	threeWire_stop();
}
//------------------------------------------------------------------------------
unsigned char ds1620_writeConfig(unsigned char data_)
{
	if(data_ > 0) 
	{
		threeWire_start();
		threeWire_write(WRITE_CONFIG, 8);
		threeWire_write(data_, 8);
		__delay_ms(50);
		threeWire_stop();
		
		if(ds1620_read(READ_CONFIG) == data_)
		{ 
			return WRITE_SUCCESSFUL;
		}
		else 
				{ 
					return WRITE_UNSUCCESSFUL;
				}
	}
	
	return BAD_CONFIG;
}
//------------------------------------------------------------------------------
// High-resolution temperature calculation. See page 4 of the datasheet for details.
//------------------------------------------------------------------------------
float ds1620_getTempFloat(void)
{
	int temp_read, count_per_c, count_remain;
	float tempr;
	
	temp_read    = ds1620_read(READ_TEMP);
	count_per_c  = ds1620_read(READ_COUNTER);
	count_remain = ds1620_read(READ_SLOPE);

	if(count_per_c != 0) // prevents division by zero		
		tempr = (calcTempr(temp_read) - 0.25) + ((count_per_c - count_remain)/count_per_c);
	
	return tempr;
}
//------------------------------------------------------------------------------
int ds1620_getTemp(char command)
{
	int rawData = ds1620_read(command);
	
	return calcTempr(rawData);
}
//------------------------------------------------------------------------------
int calcTempr(int tempr)
{
	int num = (tempr >> 1);  //Discard LSByte (Only holds fraction flag _bit - see datasheet)

	if(tempr & 0x0100) //if 9th _bit is a 1, num is negative - 2's complement (see datasheet)
	{
		num = -128 + (num & 0x7f);
	}

	return (num);	
}	
//------------------------------------------------------------------------------
#endif	