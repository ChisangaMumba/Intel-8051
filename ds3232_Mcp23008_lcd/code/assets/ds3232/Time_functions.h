#ifndef TIME_H
#define	TIME_H
//------------------------------------------------------------------------------
int get_DecTime(int time);
int get_BCDTime(int time);	
char* get_fullTimeStr(int tm[]);
char* get_wDayStr(int day);	
char* get_MonthStr(int noMonth);
char* get_fullDateStr(int tm[]);
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
char* get_fullTimeStr(int tm[])
{
  char time[8];
  
  sprintf(time,"%02d:%02d:%02d",tm[2],tm[1],tm[0]); 
  
  return time; 
}
//------------------------------------------------------------------------------
char* get_fullDateStr(int tm[])
{
  char time[20];
  
  sprintf(time,"%d/%s/20%02d",tm[4], get_MonthStr(tm[5]), tm[6]);
	
  return time; 
}
//--------------------------Week Day--------------------------------------------
char* get_wDayStr(int day)
{  
  char * wDay;
  
  switch(day)
  {
    case 1:  wDay = "Sun"; break;
    case 2:  wDay = "Mon"; break;
    case 3:  wDay = "Tue"; break;
    case 4:  wDay = "Wed"; break;
    case 5:  wDay = "Thu"; break;
    case 6:  wDay = "Fri"; break;
    case 7:  wDay = "Sat"; break;
    default: wDay = "err";           
  }
  
  return wDay;  
}
//------------------------------------------------------------------------------
char* get_MonthStr(int noMonth)
{
  char * month;  
  
  switch(noMonth)
  {
    case  1:  month = "Jan";   break;
    case  2:  month = "Feb";   break;
    case  3:  month = "March"; break;
    case  4:  month = "April"; break;
    case  5:  month = "May";   break;
    case  6:  month = "June";  break;
    case  7:  month = "July";  break;
    case  8:  month = "Aug";   break;
    case  9:  month = "Sept";  break;
    case 10:  month = "Oct";   break;
    case 11:  month = "Nov";   break;
    case 12:  month = "Dec";   break;
    default:  month = "err";           
  }
  
  return month;
}
//------------------------------------------------------------------------------
#endif