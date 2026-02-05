#ifndef MCP9800_PROTOTYPES_H
#define	MCP9800_PROTOTYPES_H
//----------------------------mcp9800--------------------------------------------
#define TEMP_REG    0x00
#define CONFIG_REG  0x01
#define THYST_REG  	0x02
#define TSET_REG   	0x03
#define RES09_BIT		0x00		 //0.5°C (Power-up default)
#define RES10_BIT		0x20		 //0.25°C 
#define RES11_BIT		0x40		 //0.125°C
#define RES12_BIT		0x60		 //0.0625°C
#define Rd          1
#define Wr          0
#define	DEG_SYMBOL	0xDF     //223 (0xDF) is ° symbol. Not a standard ascii character
//------------------------------------------------------------------------------
void mcp9800_init(unsigned char addr, unsigned char res);
void mcp9800_write(unsigned char addr, unsigned char reg, unsigned int settings);
int  mcp9800_read(unsigned char addr, unsigned char reg);
void mcp9800_writeConfig(unsigned char addr, unsigned char settings);
unsigned char mcp9800_readConfig(unsigned char addr);
//------------------------------------------------------------------------------
float toFloat(signed int tempr, unsigned char resInd);
//------------------------------------------------------------------------------
#endif