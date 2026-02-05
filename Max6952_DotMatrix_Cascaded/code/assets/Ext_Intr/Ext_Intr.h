#ifndef EXTINTERRUPT_H
#define	EXTINTERRUPT_H
//------------------------------------------------------------------------------
bit tempMode = 0;  //0 = Celcius, 1 = farhenheit
//------------------------------------------------------------------------------
void ExtInt0_init()
{
	IT0 = 1;      //Edge triggered _interrupt mode (Neg Edge)
	EX0 = 1;      //Enable external _interrupt INT0
	EA  = 1;      //Enable global interrupts
}
//------------------------------------------------------------------------------
void ExtInt0_isr(void) interrupt 0     
{
	tempMode = !tempMode;  //Toggle temperature mode
} 
//------------------------------------------------------------------------------
#endif