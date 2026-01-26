#ifndef EXTINTERRUPT_H
#define	EXTINTERRUPT_H
//------------------------------------------------------------------------------
sbit LED0 = P1^0;		
sbit LED1 = P1^1;
//------------------------------------------------------------------------------
void ExtInt0_init()
{
	IT0 = 1;      //Edge triggered _interrupt mode (Neg Edge)
	EX0 = 1;      //Enable external _interrupt INT0
	EA  = 1;      //Enable global interrupts
	
	LED0 = 1;
	LED1 = 0;
}
//------------------------------------------------------------------------------
// INT0 ISR
void ExtInt0_isr(void) interrupt 0     
{
	LED0 = ~LED0;   //Toggle LED pin
	LED1 = !LED0;   //LED1 always opposite of LED0
} 
//------------------------------------------------------------------------------
#endif