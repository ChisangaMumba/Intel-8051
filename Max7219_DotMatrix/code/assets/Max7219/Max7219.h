#ifndef MAX7219_H
#define	MAX7219_H
//------------------------Dot Matrix LED  Driver--------------------------------
#include <string.h>
#include <stdio.h>
#include "../Soft_SPI/Soft_SPI.h"
#include "ascii_chars.h"
#include "MAX7219_Prototypes.h"
//------------------------------------------------------------------------------
void MAX7219_init(char noChips)
{
  SPI_init();
  while(noChips)
        MAX7219_config(--noChips);
}
//------------------------------------------------------------------------------
void MAX7219_config(char chip)
{
  MAX7219_write(DECODE_MODE_REG,DISABLE_DECODE,chip);    
  MAX7219_write(INTESITY_REG,BRIGHTNESS,chip);     
  MAX7219_write(SCAN_LIMIT_REG,SCAN_ALL_DIGITS,chip);     
  MAX7219_write(SHUTDOWN_REG,NORMAL_OPERATION,chip);
  MAX7219_write(DISPLAY_TEST_REG,DISABLE_TEST,chip);   
}
//------------------------------------------------------------------------------
void MAX7219_write(char regName, char _data, char chip)
{
  CS1 = 0;
   
  SPI_write(regName); 
  SPI_write(_data); 
  while(chip--)
       MAX7219_NoOperation();        //Used for daisy chained (Cascaded) arrangements
  
  CS1 = 1;
}
//------------------------------------------------------------------------------
void MAX7219_displayText(char* text)
{ 
  char col, chip = 0;
 
  while(*text)
  { 
    char row = (*text++) - 32;//(Text-32)...because the first 32 ASCII character codes are none Printable (control chars)
    
    for(col = 0; col < 8; col++)
    {
      MAX7219_write( col, symbol[row][col], chip );
    }
    
    chip++;
  }
}
//-----------Passes the data to the adjacent MAX7219 in the Daisy Chain---------
void MAX7219_NoOperation()
{
  SPI_write(NO_OP_REG);           
  SPI_write(0x00);                //Don't care (Can be any arbitrary value)
}
//------------------------------------------------------------------------------
#endif		