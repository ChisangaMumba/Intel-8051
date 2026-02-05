#ifndef EXTINTERRUPT_H
#define	EXTINTERRUPT_H
//------------------------------------------------------------------------------
bit sensorMode = 0;  //0 = Temperature, 1 = Relative Humidity
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
	sensorMode = !sensorMode;  //Toggle sensor mode
} 
//------------------------------------------------------------------------------
#endif