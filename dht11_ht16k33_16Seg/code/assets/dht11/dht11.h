#ifndef DHT11_H
#define	DHT11_H
//------------------------------------------------------------------------------
#include <./assets/oneWire/oneWire.h>
//------------------------------------------------------------------------------
int dht11_calcChecksum(unsigned char sensorData[])
{
	int checksum = 0;
	
	char i;
	for(i = 0; i < 4; i++)
	{
		checksum += sensorData[i];
	}
	
	return checksum;
}
//------------------------------------------------------------------------------
unsigned char dht11_isChecksumValid(unsigned char sensorData[])
{
	unsigned char isValid = 0;
	
	if(dht11_calcChecksum(sensorData) != sensorData[4]) // sensorData[4] == checksum value
	{
		isValid = 1;
	}
	
	return isValid;
}
//------------------------------------------------------------------------------
int dht11_getTemperature(unsigned char sensorData[])
{
  int tempr = (sensorData[3] << 8) + sensorData[2];
    
  return tempr;
}
//------------------------------------------------------------------------------
int dht11_getHumidity(unsigned char sensorData[])
{
  int humidity = (sensorData[1] << 8) + sensorData[0];
    
  return humidity;
}
//------------------------------------------------------------------------------
void dht11_getSensorData(unsigned char sensorData[])
{
	unsigned char i;
	for(i = 0; i < 5; i++)
	{
		sensorData[i] = oneWire_readByte();
	}
}
//------------------------------------------------------------------------------
#endif