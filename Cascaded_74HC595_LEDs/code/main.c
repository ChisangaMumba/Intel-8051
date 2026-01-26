#include<reg52.h>
#include <stdio.h>
#include <./assets/TC72/TC72.h>
#include <./assets/Segments/Segments.h>
//------------------------------------------------------------------------------
signed int tempr;
char out[30];
//------------------------------------------------------------------------------
int main() 
{	
	TC72_Init();
	Segments_init();
	
  while(1)
  { 
		tempr = TC72_ReadTempr();		  			 
		tempr = toFloat(tempr) * 10;
		
		Segments_display( FIFO, tempr );
  }
}
//------------------------------------------------------------------------------