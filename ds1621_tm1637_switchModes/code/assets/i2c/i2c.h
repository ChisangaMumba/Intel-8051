#ifndef I2C_H
#define I2C_H
//------------------------------------------------------------------------------
#define ACK  0
#define NACK 1
//------------------------------------------------------------------------------
sbit SCL = P3^6;
sbit SDA = P3^7;
//------------------------------------------------------------------------------ 
void I2C_init()
{
	SDA = 1;
	SCL = 1;
}
//------------------------------------------------------------------------------ 
void I2C_start()
{
	SDA = 0;
	SCL = 0;
}
//------------------------------------------------------------------------------ 
void I2C_restart()
{
	SDA = 1;
	SCL = 1;
	SDA = 0;
	SCL = 0;
}
//------------------------------------------------------------------------------ 
void I2C_stop()
{
	SCL = 0;
	SDA = 0;
	SCL = 1;
	SDA = 1;
}
//------------------------------------------------------------------------------ 
void I2C_ack(char ackn)
{
	SDA = ackn;
	SCL = 1;
	SCL = 0;
	SDA = 1;
}
//------------------------------------------------------------------------------ 
unsigned char I2C_write(unsigned char _data)
{
	//Function Purpose: I2C_Write_Byte transfers one byte
	char tx;
	
  for(tx = 0; tx < 8; tx++)
  {
    SDA = ((_data << tx) & 0x80) ? 1 : 0 ; //MSB first
    SCL = 1;
		SCL = 0;                   //Toggle SCK pin So that slave can latch _data _bit
  }
	
  I2C_ack(ACK);
	
  return SDA;
}
//------------------------------------------------------------------------------ 
unsigned char I2C_read(char ackState)
{
	unsigned char bitValue, rx, _data = 0;
	
	for(rx = 0; rx < 8; rx++) 
	{
		SCL = 1;

		bitValue = SDA;
		_data += ( bitValue << (7-rx) );

		SCL = 0;
	}
	
	I2C_ack(ackState);
	
	return _data;
}
//------------------------------------------------------------------------------
#endif