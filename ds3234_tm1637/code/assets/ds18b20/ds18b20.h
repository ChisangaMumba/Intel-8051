#ifndef DS18B20_H
#define	DS18B20_H
//------------------------------------------------------------------------------
#define FRAC_FLAG           0x000F
#define SKIP_ROM            0xCC
#define START_CONVERSION    0x44
#define READ_TEMPERATURE    0xBE
//------------------------------------------------------------------------------
sbit DQ_PIN = P3^3;
//------------------------------------------------------------------------------ 
void delay(unsigned int i)
{
  while(i--);
}
//------------------------------------------------------------------------------
char ds18b20_start()
{
	char ack = 0;
	
  DQ_PIN = 1;           
  delay(8);      
	DQ_PIN = 0;       
  delay(80);      
	DQ_PIN = 1;
	delay(14);
	ack = DQ_PIN;
	delay(20);
	
	return ack;
}
//------------------------------------------------------------------------------ 
void ds18b20_writeByte(char _data)
{
  unsigned char i = 0;

	for(i = 8; i > 0; i--)
	{
		DQ_PIN = 0;
		DQ_PIN = _data & 0x01;
		delay(5);
		DQ_PIN = 1;
		_data >>= 1;
	}	
}
//------------------------------------------------------------------------------ 
char ds18b20_readByte()
{
  unsigned char i, _data = 0;
    
	for(i = 8; i > 0; i--)
  {
		DQ_PIN = 0;
		_data >>= 1;
		DQ_PIN = 1;
		if(DQ_PIN)
		{
			_data += 0x80;
		}
		delay(4);
   }
   
	 return(_data);
}
//------------------------------------------------------------------------------
void ds18b20_command(char _data)
{
  ds18b20_start();
  ds18b20_writeByte(SKIP_ROM);   
  ds18b20_writeByte(_data);  	
}
//------------------------------------------------------------------------------
signed int ds18b20_read()
{
	unsigned char tempr[2];
	
	ds18b20_command(START_CONVERSION);
	ds18b20_command(READ_TEMPERATURE);
	
	tempr[0] = ds18b20_readByte();
  tempr[1] = ds18b20_readByte();
	 
	return ((tempr[1] << 8) + tempr[0]);
}
//------------------------------------------------------------------------------
float ds18b20_toFloat(signed int tempr)
{
  float result = (float)(tempr>>4);     
  char count = tempr & FRAC_FLAG;          
  
  if(count) 
  {
    result += (count * 0.0625);
  }
  
  return result;
}
//------------------------------------------------------------------------------
#endif	/* DS18B20_H */