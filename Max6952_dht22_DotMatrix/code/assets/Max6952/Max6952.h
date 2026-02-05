#ifndef MAX6952_H
#define	MAX6952_H
//------------------------Dot Matrix LED  Driver--------------------------------
#include "MAX6952_Prototypes.h"
//------------------------------------------------------------------------------
void MAX6952_init(char noChips)
{
  SPI_init();
  while(noChips)
			MAX6952_config(--noChips);
}
//------------------------------------------------------------------------------
void MAX6952_config(char chip)
{
  MAX6952_write(DECODE_MODE_REG, DECODE_ALL, chip);    //Decodes ascii characters
  MAX6952_write(INTESITY_REG10, BRIGHTNESS, chip); 
  MAX6952_write(INTESITY_REG32, BRIGHTNESS, chip);
  MAX6952_write(SCAN_LIMIT_REG, SCAN_LOW_NIBBLE, chip);
  MAX6952_write(SHUTDOWN_REG, NORMAL_OPERATION, chip);
}
//------------------------------------------------------------------------------
void MAX6952_write(char reg, signed char data_, char chip)
{
  CS = 0; 
  
  SPI_write(reg); 
  SPI_write(data_); 
  while(chip--)
      MAX6952_NoOperation();        //Used for daisy chained (Cascaded) arrangements
		
  CS = 1;
}
//------------------------------------------------------------------------------
void MAX6952_displayNumber(long number)
{   
	char strNum[15]; 
  sprintf(strNum, "%6li", number);
  
	MAX6952_displayText(strNum);
}
//------------------------------------------------------------------------------
void MAX6952_displayText(char text[])
{
	char count = 0, i, chr, chip;
						
  for(i = 0; i < strlen(text); i++)
  {  
		chr = text[i];			
		
		if(chr & 0x80)
			chr = getCustomChar(chr); //All non-standard ascii chars are above 128
		
		chip = getChipNum(i);
		MAX6952_write( DISPLAY_REG0 + count, chr, chip);
		
		count = (count >= 3) ? 0 : count + 1;
  }
}
//----------Passes the data_ to the adjacent MAX6952 in the Daisy Chain---------
void MAX6952_NoOperation(void)
{
  SPI_write(NO_OP_REG);           
  SPI_write(0x00);                
}
//------------------------------------------------------------------------------
char getChipNum(char charPos)
{
	char chipNum;
	
	if(charPos >= 0 && charPos <= 3)
		chipNum = 0;
	else
			if(charPos >= 4 && charPos <= 7)
				chipNum = 1;
			else
				  if(charPos >= 5 && charPos <= 11)
						chipNum = 2;
					
	return chipNum;
}
//------------------------------------------------------------------------------
char getCustomChar(char asciiChar)
{
	char i = 0, digit = 0x00;
  
	while(customChar[i])
	{
		 if(asciiChar == customChar[i])
		 {
		   digit = charCode[i]; 
			 break;
		 }
		 i++;
	}	
					
	return digit;			
}
//------------------------------------------------------------------------------
#endif	