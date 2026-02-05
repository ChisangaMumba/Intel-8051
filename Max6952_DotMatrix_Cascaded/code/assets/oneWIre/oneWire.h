#ifndef ONEWIRE_H
#define	ONEWIRE_H
//------------------------------------------------------------------------------
sbit DATA_PIN = P3^0;		
//------------------------------------------------------------------------------
void timer_start()
{
	TR0 = 1;					// Start timer0 
	while(TF0 == 0);	// Wait until timer0 flag set
	TR0 = 0;					// Stop timer0 
	TF0 = 0;					// Clear timer0 flag 
}
//------------------------------------------------------------------------------
void timer_delay20ms()		// Timer0 delay function
{
	TMOD = 0x01;			// Timer0 mode1 (16-bit_ timer mode)
	TH0 = 0xB8;				// Load higher byte in TH0 
	TL0 = 0x0C;				// Load lower byte in TL0 
	
	timer_start();
}
//------------------------------------------------------------------------------
void timer_delay30us()		
{
	TMOD = 0x01;			
	TH0 = 0xFF;				
	TL0 = 0xF1;				
	
	timer_start();
}
//------------------------------------------------------------------------------
void oneWire_start()			// Microcontroller send request
{
	DATA_PIN = 0;		
	timer_delay20ms();	
	DATA_PIN = 1;		
}
//------------------------------------------------------------------------------
unsigned char oneWire_getResponse()			
{
	unsigned char response = 0;
	
	while(DATA_PIN == 1);
	while(DATA_PIN == 0);
	while(DATA_PIN == 1);
	
	response = 1;
	
	return response;
}
//------------------------------------------------------------------------------
unsigned char oneWire_readByte()		
{
	unsigned char i, dataByte = 0;	
	
	for(i = 0; i < 8; i++)
	{
		while(DATA_PIN == 0);  // check received _bit 0 or 1 
		
		timer_delay30us();		
		if(DATA_PIN == 1)	//If high pulse is greater than 30ms
		{
			dataByte += (0x01 << (7 - i));    // set _bit (7 - i)
		}
		
		while(DATA_PIN == 1);
	}
	
	return dataByte;
}
//------------------------------------------------------------------------------
#endif