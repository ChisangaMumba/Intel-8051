#ifndef LCD_Serial_H
#define LCD_Serial_H
//------------------------------------------------------------------------------
#include "LCD_Serial_Prototypes.h"
#include <./assets/delay/delay.h>
#include <./assets/i2c/i2c.h>
//------------------------------------------------------------------------------
void LCD_init()
{
	_delay_ms(30);
	
  I2C_init();    
  
	I2C_start();              
	I2C_write(DEV_ADDR);             
  
	LCD_command(home);
  LCD_command(function_set4);
	LCD_command(font2a);
  LCD_command(display_on);
  LCD_command(clear); 
	
	I2C_stop();
}
//------------------------------------------------------------------------------
void LCD_command(char data_)
{
	I2C_write(CMD_REG);									//C0=1 RS=0 (Instruction Register ( commands ))
	I2C_write(data_);
}
//------------------------------------------------------------------------------
void LCD_setPos(char data_)
{
	I2C_start();              
	I2C_write(DEV_ADDR); 
	
  LCD_command(data_);  
	
	I2C_stop();
}
//------------------------------------------------------------------------------
void LCD_string(char row, char col, char * text)
{
	LCD_setPos(RowAddr[row] + col);
	
	I2C_start(); 
	
	I2C_write(DEV_ADDR); 
	I2C_write(DAT_REG);								//C0=0 RS=0 Data Register (Strings and characters).	
  while(*text)
  {
    I2C_write(*text++);
  }
	
	I2C_stop();
}
//------------------------------------------------------------------------------
#endif