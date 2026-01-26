
#ifndef SR_74HC595_PROTOTYPES_H
#define	SR_74HC595_PROTOTYPES_H
//------------------------------------------------------------------------------
#define  FIFO           0   //FIFO - First In First Out
#define  LIFO           1   //LIFO - Last In First Out
#define  DECIMAL_POINT  0x7F
//------------------------------------------------------------------------------
void ShiftReg_LIFOSend(char text[]);
void ShiftReg_FIFOSend(char text[]);
char getDigit(char pos, char asciiChar);
char* get_lastCharAddr(char text[]);
//------------------------------------------------------------------------------
#endif

