#include<reg52.h>
#include <stdio.h>
#include <stdlib.h>
#include <./assets/mcp9800/mcp9800.h>
#include "assets/lcd/LCD_Serial.h"
//------------------------------------------------------------------------------
unsigned char addr = 0x90; // Temperature sensor device Address
float tempr;
unsigned char resNum;
char str[18];
//------------------------------------------------------------------------------
int main() 
{
  LCD_init(0x4E);       	 // Expander Address  
  mcp9800_init(addr, RES12_BIT);   
  resNum = mcp9800_getResolutionNum(addr);	
	LCD_string(0,5,"MCP9800");
	  
	while(1)
  {
		tempr = mcp9800_read(addr, TEMP_REG);
    
    sprintf(str,"Temp: %8.4f%cC", toFloat(tempr, resNum), DEG_SYMBOL);
    LCD_string(1,0,str);    
  }
}
//------------------------------------------------------------------------------