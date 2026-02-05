#ifndef DS1631_PROTOTYPES_H
#define	DS1631_PROTOTYPES_H
//----------------------------DS1631--------------------------------------------
#define CONFIG_REG   0xAC
#define TEMP_REG     0xAA
#define TH_REG    	 0xA1
#define TL_REG    	 0xA2
#define START_CONV   0x51
#define STOP_CONV    0x22
#define CONT_CONV    0x02
#define SOFT_POR     0x54
#define RES09_BIT		 0x00		 //0.5000°C  93.75ms conversion time
#define RES10_BIT		 0x04		 //0.2500°C  187.5ms conversion time
#define RES11_BIT		 0x08		 //0.1250°C  375ms conversion time
#define RES12_BIT		 0x0C		 //0.0625°C  (Power-up default) 750ms conversion time
#define Rd           1
#define Wr           0
#define FRAC_FLAG    0x00F0
#define	DEG_SYMBOL	 0xDF     //223 (0xDF) is ° symbol. Not a standard ascii character
//------------------------------------------------------------------------------
void ds1631_init(unsigned char addr, unsigned char resolution);
void ds1631_config(unsigned char addr, unsigned char command);
void ds1631_convertCmd(unsigned char addr, unsigned char command);
unsigned char ds1631_read1ByteReg(unsigned char addr, unsigned char deviceReg);
int  ds1631_read2ByteReg(unsigned char addr, unsigned char deviceReg);
void ds1631_write2ByteReg(unsigned char addr, unsigned char deviceReg, unsigned int settings);
//------------------------------------------------------------------------------
float toFloat(signed int tempr, unsigned char resInd);
//------------------------------------------------------------------------------
#endif