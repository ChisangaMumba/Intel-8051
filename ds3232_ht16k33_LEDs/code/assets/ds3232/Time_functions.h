#ifndef TIME_H
#define	TIME_H
//-----------------------Change BCD time to Decimal-----------------------------
int get_DecTime(int time)
{   
  return ((time >> 4) * 10) + (time & 0x0F);  
}
//-----------------------Change Decimal time to BCD-----------------------------
int get_BCDTime(int time)
{
  return ((time / 10) << 4) + (time % 10);
}
//------------------------------------------------------------------------------
char* get_TimeStr(int tm[])
{
  char timeStr[8];
  
  sprintf(timeStr, "%02d%02d%02d", tm[2], tm[1], tm[0]); 
  
  return timeStr; 
}
//------------------------------------------------------------------------------
char* get_DateStr(int tm[])
{
  char timeStr[8];
  
	sprintf(timeStr, "%02d%02d%02d", tm[4], tm[5], tm[6]); 
	
  return timeStr; 
}
//------------------------------------------------------------------------------
#endif