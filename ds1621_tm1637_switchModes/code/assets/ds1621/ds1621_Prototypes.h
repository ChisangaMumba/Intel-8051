#ifndef DS1621_PROTOTYPES_H
#define	DS1621_PROTOTYPES_H
//----------------------------DS1621--------------------------------------------
#define CONFIG_REG  0xAC
#define START_CONV  0xEE
#define TEMP_REG    0xAA
#define CONT_CONV   0x02
#define FRAC_FLAG   0x0080
#define Rd          1
#define Wr          0
#define	DEG_SYMBOL	0xDF     //223 (0xDF) is ° symbol. Not a standard ascii character
//------------------------------------------------------------------------------
void ds1621_init(unsigned char Addr);
void ds1621_config(unsigned char Addr);
void ds1621_startConv(unsigned char Addr);
int  ds1621_readTemp(unsigned char Addr);
//------------------------------------------------------------------------------
float toFloat(signed int tempr);
//------------------------------------------------------------------------------
#endif