#ifndef  DS1307_PROTOTYPES_H
#define  DS1307_PROTOTYPES_H
//------------------------------------------------------------------------------
#define WRITE_CMD     0xD0
#define READ_CMD      0xD1
//------------------------------------------------------------------------------
void ds1307_init(void);
int ds1307_readReg(int addr);
void ds1307_getDateTime(int time[]);
void ds1307_setDateTime(int regAddr, int _data);
//------------------------------------------------------------------------------
#endif