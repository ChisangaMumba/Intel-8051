#ifndef TC77_PROTOTYPES_H
#define TC77_PROTOTYPES_H
//------------------------------------------------------------------------------
#define SHUTDOWN_MODE      0xFF
#define CONTINUOUS_CONV    0x00
#define FRAC_FLAG          0x0078
#define	DEG_SYMBOL			 	 0xDF     //223 (0xDF) is ° symbol. Not a standard ascii character
//------------------------------------------------------------------------------
void TC77_init(void);
signed int TC77_read(void);
float toFloat(signed int tempr);
//------------------------------------------------------------------------------
#endif 