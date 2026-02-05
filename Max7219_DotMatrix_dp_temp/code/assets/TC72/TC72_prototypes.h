#ifndef TC72_PROTOTYPES_H
#define	TC72_PROTOTYPES_H
//------------------------------------------------------------------------------
#include "../Soft_SPI/Soft_SPI.h"
#include "./assets/delay/delay.h"
#include <math.h>
//------------------------------------------------------------------------------
#define CONTROL_REG   0x80
#define START_CONV    0x10
#define TEMPR_REG     0x02
#define FRAC_FLAG     0x00C0
//------------------------------------------------------------------------------
void TC72_init(void);
int TC72_readTempr();
float toFloat(signed int tempr);
//------------------------------------------------------------------------------
#endif

