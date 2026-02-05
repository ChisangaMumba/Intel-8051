#ifndef DHT22_H
#define	DHT22_H
//------------------------------------------------------------------------------
#include <assets/oneWire/oneWire.h>
#include <assets/Ext_Intr/Ext_Intr.h>
#include <assets/dht22/dht22_prototypes.h>
//------------------------------------------------------------------------------
void dht22_init()
{
	ExtInt0_init();
}
//------------------------------------------------------------------------------
unsigned char dht22_calcChecksum(unsigned char sensorData[])
{
	unsigned char i, checksum = 0;
	
	for(i = 0; i < 4; i++)
	{
		checksum += sensorData[i];
	}
	
	return checksum;
}
//------------------------------------------------------------------------------
unsigned char dht22_isChecksumInvalid(unsigned char sensorData[])
{
	unsigned char isInvalid = 0;
	
	if(dht22_calcChecksum(sensorData) != sensorData[4]) // sensorData[4] == checksum value
	{
		isInvalid = 1;
	}
	
	return isInvalid;
}
//------------------------------------------------------------------------------
signed int dht22_getTemperature(unsigned char sensorData[])
{
  signed int tempr = (sensorData[2] << 8) + sensorData[3];
    
  return tempr;
}
//------------------------------------------------------------------------------
int dht22_getHumidity(unsigned char sensorData[])
{
  int humidity = (sensorData[0] << 8) + sensorData[1];
    
  return humidity;
}
//------------------------------------------------------------------------------
void dht22_getSensorData(unsigned char sensorData[])
{
	unsigned char i;
	for(i = 0; i < 5; i++)
	{
		sensorData[i] = oneWire_readByte();
	}
}
//------------------------------------------------------------------------------
 float calcTempr(signed int rawData)
{
	float tempr = rawData ;  
   	
	if(rawData & 0x8000) //if 16th _bit is a 1, num is negative (sign magnitude signed number)
	{
	  tempr = -1 * (rawData & 0x7fff);
	}

	return (modeNum == 0) ? tempr/10 : ((float) (tempr/10) * 9/5) + 32; // C or F
}
//------------------------------------------------------------------------------
#endif