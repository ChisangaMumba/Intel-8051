#ifndef THREE_WIRE_H
#define	THREE_WIRE_H
//------------------------------------------------------------------------------
//Configuration Status
#define WRITE_SUCCESSFUL      0x00
#define WRITE_UNSUCCESSFUL    0x01
#define BAD_CONFIG            0x02
//------------------------------------------------------------------------------
void threeWire_start(void);
void threeWire_stop(void);
int threeWire_read(void);
void threeWire_write(int data_, char sz);
//------------------------------------------------------------------------------
sbit DQ   = P3^2;
sbit CLK  = P3^3;
sbit RST  = P3^4;
//------------------------------------------------------------------------------
void threeWire_start(void)
{
	RST = 0;
	CLK = 1;
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
		CLK = 0;
		DQ = ((data_ >> tx) & 0x01) ? 1 : 0;
		CLK = 1;
	}
}
//------------------------------------------------------------------------------
int threeWire_read(void)
{	
	char rx;
	int data_ = 0;

	DQ = 1;
	
	for(rx = 0; rx < 9; rx++)
	{
		CLK = 0;
		if(DQ) data_ += 0x01 << rx;
		CLK = 1;
	}
	
	DQ = 0;

	return data_;
}
//------------------------------------------------------------------------------
#endif	