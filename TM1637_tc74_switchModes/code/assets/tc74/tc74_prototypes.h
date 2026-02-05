#ifndef TC74_PROTOTYPES_H
#define	TC74_PROTOTYPES_H
//------------------------------------------------------------------------------
#define  TEMPR_REG     	 0x00
#define  CONFIG_REG      0x01
#define  READ            0x9A     
#define  WRITE           0x9B     
#define  STANDBY_MODE		 0x80
#define  NORMAL_MODE		 0x00
#define	 DEG_SYMBOL			 0xDF     //223 (0xDF) is ° symbol. Not a standard ascii character
//------------------------------------------------------------------------------
void TC74_init(char _data);
void TC74_config(char _data);
signed char TC74_read(char regAddress);
//------------------------------------------------------------------------------
#endif