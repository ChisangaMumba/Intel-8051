#ifndef LM75_PROTOTYPES_H
#define	LM75_PROTOTYPES_H
//------------------------------------------------------------------------------
#define  LM75_ADDRESS             0x90     // Address + Read bit
#define  TEMPERATURE_ADDRESS      0x00
#define  CONFIGURATION_ADDRESS    0x01
#define  THYST_ADDRESS            0x02     
#define  TOS_ADDRESS              0x03
#define  FRACTION_FLAG            0x0080   // 0.5 Bit Flag
#define	 DEG_SYMBOL								0xDF     //223 (0xDF) is ° symbol. Not a standard ascii character
//------------------------------------------------------------------------------
void  LM75_init(void);
float LM75_read(char regAddress);
void  LM75_setConfig(char _data);
char  LM75_readConfig(void);
void  LM75_set(char regAddress, signed int _data);
float toFloat(signed int tempr);
//------------------------------------------------------------------------------
#endif