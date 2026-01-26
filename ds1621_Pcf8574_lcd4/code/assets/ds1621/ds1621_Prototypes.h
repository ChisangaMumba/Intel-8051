#ifndef DS1621_PROTOTYPES_H
#define	DS1621_PROTOTYPES_H
//----------------------------DS1621--------------------------------------------
#define CONFIG_REG   0xAC
#define TEMP_REG     0xAA
#define TH_REG    	 0xA1
#define TL_REG    	 0xA2
#define START_CONV   0xEE
#define STOP_CONV    0x22
#define READ_COUNTER 0xA8
#define READ_SLOPE   0xA9
#define CONT_CONV    0x02
#define FRAC_FLAG    0x0080
#define Rd           1
#define Wr           0
#define	DEG_SYMBOL	 0xDF     //223 (0xDF) is ° symbol. Not a standard ascii character
//------------------------------------------------------------------------------
void ds1621_init(unsigned char addr);
void ds1621_config(unsigned char addr);
void ds1621_convertCmd(unsigned char addr, unsigned char command);
unsigned char ds1621_read1ByteReg(unsigned char addr, unsigned char deviceReg);
int  ds1621_read2ByteReg(unsigned char addr, unsigned char deviceReg);
void ds1621_write2ByteReg(unsigned char addr, unsigned char deviceReg, unsigned int settings);
//------------------------------------------------------------------------------
float toFloat(signed int tempr);
//------------------------------------------------------------------------------
#endif