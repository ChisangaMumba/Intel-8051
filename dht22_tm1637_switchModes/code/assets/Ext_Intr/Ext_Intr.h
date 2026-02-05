#ifndef EXT_INTERRUPT_H
#define	EXT_INTERRUPT_H
//------------------------------------------------------------------------------
char modeNum = 0;  //0, 1 = temperature (°C and °F respectively), 2 = humidity
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
	modeNum += 1;
	modeNum = (modeNum > 2) ? 0 : modeNum;
} 
//------------------------------------------------------------------------------
#endif