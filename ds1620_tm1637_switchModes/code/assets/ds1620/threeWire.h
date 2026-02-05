#ifndef THREE_WIRE_H
#define	THREE_WIRE_H
//------------------------------------------------------------------------------
sbit DQ   = P3^5;
sbit SCLK  = P3^6;
sbit RST  = P3^7;
//------------------------------------------------------------------------------
void threeWire_start(void);
void threeWire_stop(void);
int threeWire_read(void);
void threeWire_write(int data_, char sz);
//------------------------------------------------------------------------------
void threeWire_start(void)
{
	RST = 0;
	SCLK = 1;
	RST = 1;
}
//------------------------------------------------------------------------------
void threeWire_stop(void)
{
	RST = 0;
}
//------------------------------------------------------------------------------
void threeWire_write(int data_, char sz)
{
	int tx;
	for(tx = 0; tx < sz; tx++)
	{
		SCLK = 0;
		DQ = ((data_ >> tx) & 0x01) ? 1 : 0;
		SCLK = 1;
	}
}
//------------------------------------------------------------------------------
int threeWire_read(void)
{	
	char rx, _bit = 0;
	int data_ = 0;

	DQ = 1;
	
	for(rx = 0; rx < 9; rx++)
	{
		SCLK = 0;
		if(DQ) data_ += (0x01 << rx);
		SCLK = 1;
	}
	
	DQ = 0;

	return data_;
}
//------------------------------------------------------------------------------
#endif