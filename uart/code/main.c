#include <reg51.h>
//--------------------------------------------------------
#define XTAL 24000000
void uart_init()
{
	TMOD = 0x20; //Timer 1 In Mode 2 -Auto Reload to Generate Baud Rate
	SCON = 0x50; //Serial Mode 1, 8-Data Bit, REN Enabled
	TH1  = 0xFD; //Load Baud Rate 9600 To Timer Register
	//TL1  = 0xFD;
	TR1  = 1;		 //Start Timer
	
	/*
	SCON=0X50;//8 bit 1 start
	TMOD=0X20;//8 bit mode2
	TH1=0Xfd;//253 baud rate 9600
	TR1=1;//start timer
	*/
}
//--------------------------------------------------------
void uart_tx(unsigned char dat)
{
	SBUF = dat;
	while(TI==0);  //wait for transmit
	TI = 0;
}
//--------------------------------------------------------
unsigned char uart_rx()
{
  /*
	while(!RI);
	RI = 0;
	return SBUF;
	*/

	unsigned char chr;
	
	while(RI == 0);	//wait for receive
	chr = SBUF;			//save char
	RI = 0;
	
	return(chr);
}
//--------------------------------------------------------
void uart_msg(unsigned char *chr)
{
  while(*chr)
  {
    uart_tx(*chr++);
  }
}
//--------------------------------------------------------
int main()
{
	uart_init();
	
	uart_msg("Hello World!\r\n");
	while(1)
	{

	}
}
//--------------------------------------------------------