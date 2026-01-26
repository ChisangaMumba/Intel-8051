#ifndef SEGMENT_FUNCTIONS_H
#define	SEGMENT_FUNCTIONS_H
//------------------------------------------------------------------------------
#include "./assets/soft_spi/Soft_SPI.h"
#include "../74HC595/74HC595.h"
//------------------------------------------------------------------------------
void Segments_init()
{
    SPI_init();
}
//------------------------------------------------------------------------------
void Segments_display(char sendMode, signed int number)
{     
  char strNum[10];
  sprintf(strNum,"%4i",number);
  
  switch(sendMode)
  {
    case 0: ShiftReg_FIFOSend(strNum); break;  
    case 1: ShiftReg_LIFOSend(strNum); break;
  }
}
//------------------------------------------------------------------------------
#endif