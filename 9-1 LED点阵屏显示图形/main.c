#include <REGX52.H>
#include "Delay.h"
sbit RCK = P3^5;  //RCLK
sbit SCK = P3^6;
sbit SER = P3^4;

void _74HC595_WriteByte(unsigned char Byte)
{
	unsigned char i;
		for(i = 0;i< 8;i++)
	{	
		SER = Byte&(0x80>>i);
		SCK = 1;
		SCK = 0;
	}
	RCK = 1;
	RCK = 0;
}

void MatrixLED_ShowColumn(unsigned char column,Data)
{
		_74HC595_WriteByte(Data);
	 P0=~(0x80>>column);
}
void main()
{
	RCK = 0;
	SCK = 0;
	
		while(1)
		{	
		 MatrixLED_ShowColumn(0,0x3C);
			MatrixLED_ShowColumn(1,0x42);
			MatrixLED_ShowColumn(2,0x3C);
			MatrixLED_ShowColumn(3,0xAA);
			MatrixLED_ShowColumn(4,0xAA);
			MatrixLED_ShowColumn(5,0xAA);
			MatrixLED_ShowColumn(6,0xAA);
			MatrixLED_ShowColumn(7,0xAA);
			
		}
}