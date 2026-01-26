#ifndef UART_H
#define	UART_H
//------------------------------------------------------------------------------
void uart_init(void)
{
	TMOD = 0x20; //Timer 1 In Mode 2 -Auto Reload to Generate Baud Rate
	SCON = 0x50; //Serial Mode 1, 8-Data Bit, REN Enabled
	TH1  = 0xFD; //Load Baud Rate 9600 To Timer Register
	TR1  = 1;		 //Start Timer
}
//------------------------------------------------------------------------------
void uart_tx(uint8_t dat)
{
	SBUF = dat;
	while(TI==0);  //wait for transmit
	TI = 0;
}
//------------------------------------------------------------------------------
uint8_t uart_rx(void)
{
	uint8_t chr;
	
	while(RI == 0);	//wait for receive
	chr = SBUF;			//save char
	RI = 0;
	
	return(chr);
}
//------------------------------------------------------------------------------
void uart_msg(uint8_t *chr)
{
  while(*chr)
  {
    uart_tx(*chr++);
  }
}
//------------------------------------------------------------------------------
#endif	