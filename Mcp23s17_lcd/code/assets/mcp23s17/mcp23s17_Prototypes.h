#ifndef EXPANDER_PROTOTYPES_H
#define EXPANDER_PROTOTYPES_H
//-----------------------I/O Direction Registers(TRIS)--------------------------
#define IODIRA     0x00
#define IODIRB     0x01
//-----------------------General Purpose I/O------------------------------------
#define GPIOA      0x12   //Reading the GPIOn register reads the value on the port.
#define GPIOB      0x13
//-----------------------Output Latches-----------------------------------------
#define OLATA      0x14   //Writing to the OLATn register Writes to the associated port.
#define OLATB      0x15
//-----------------------W/R Control bytes--------------------------------------
#define WRITE      0x40   // 0b0100 + 0b000(Slave address) + 0b0(Write) => 0x40
#define READ       0x41
//---------------------------Input pin Bit postions------------------------------------
#define I0         0x01
#define I1         0x02
#define I2         0x04
#define I3         0x08
#define I4         0x10
#define I5         0x20
#define I6         0x40
#define I7         0x80
//-------------------------Function Prototypes----------------------------------
void EXPANDER_init(char portA, char portB);
void EXPANDER_write(char address, char _data);
char EXPANDER_read(char address);
//------------------------------------------------------------------------------
#endif