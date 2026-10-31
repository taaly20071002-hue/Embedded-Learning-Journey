#include <REGX52.H>
#include "Delay.h"
sbit Buzzer = P2^5;	

void Delay500us(void)
{
	unsigned char i, j;
	i = 2;
	j = 79;
	do
	{
		while (--j);
	} while (--i);
}
void Buzzer_Time(unsigned int xms)	//@12.000MHz
{
	unsigned char i;
			for(i = 0;i<xms;i++)
		  {		
			Buzzer = !Buzzer;
			Delay500us();
			}
		

	}