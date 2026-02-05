#ifndef DHT22_PROTOTYPES_H
#define	DHT22_PROTOTYPES_H
//------------------------------------------------------------------------------
void dht22_init();
unsigned char dht22_calcChecksum(unsigned char sensorData[]);
unsigned char dht22_isChecksumInvalid(unsigned char sensorData[]);
signed int dht22_getTemperature(unsigned char sensorData[]);
int dht22_getHumidity(unsigned char sensorData[]);
void dht22_getSensorData(unsigned char sensorData[]);
float calcTempr(signed int tempr);
//------------------------------------------------------------------------------
#endif