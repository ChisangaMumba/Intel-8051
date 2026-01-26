#ifndef MAX7219_H
#define	MAX7219_H
//------------------------Dot Matrix LED  Driver--------------------------------
#include <string.h>
#include <stdio.h>
#include "../Soft_SPI/Soft_SPI.h"
#include "MAX7219_Prototypes.h"
//------------------------------------------------------------------------------
void MAX7219_init(char scanSize)
{
  SPI_init();
  
  MAX7219_write(DECODE_MODE_REG, DECODE_ALL);    
  MAX7219_write(INTESITY_REG, BRIGHTNESS);     
  MAX7219_write(SCAN_LIMIT_REG, scanSize);     
  MAX7219_write(SHUTDOWN_REG, NORMAL_OPERATION);
}
//------------------------------------------------------------------------------
void MAX7219_write(char reg, signed char _data)
{
  CS1 = 0; 
  
  SPI_write(reg); 
  SPI_write(_data); 
  
  CS1 = 1;
}
//------------------------------------------------------------------------------
void MAX7219_displayNumber(signed int number)
{   
	char strNum[15]; 
  sprintf(strNum,"%4i",number);
	
	MAX7219_displayNumText(strNum);
}
//------------------------------------------------------------------------------
void MAX7219_displayNumText(char text[])
{ 
	char pos;
	
  for(pos = 0; pos < strlen(text); pos++)
  {   
    char i = text[pos];  
    MAX7219_write( pos+1, getDigit(pos,i) );
  }
}
//------------------------------------------------------------------------------
char getDigit(char pos, char number)
{
    char digit = 0;
    
    if(number >= '0' && number <= '9') 
    {
        digit = (pos == 1 || pos == 3) ? (number + DECIMAL_POINT) : number ;
    }
    else
        if(number == '-')
        {
            digit = (pos == 1 || pos == 3) ? (0 + DECIMAL_POINT) : 0x0A;  //0x0A - minus symbol see MAX7219 datasheet
        }
        else
            if(number == ' ')
            {
                digit = (pos == 1 || pos == 3) ? (0 + DECIMAL_POINT) : 0x0F; //0x0F - blank. used for leading zero suppression
            }
    
    return digit;
}
//------------------------------------------------------------------------------
#endif	