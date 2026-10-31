#include <REGX52.H>
#include "Timer0.h"
#include "Nixie.h"
#include "Key.h"
#include "Delay.h"

unsigned char KeyNum;
unsigned char Temp;

void main()
{
	Timer0_Init();

	while(1)
	{
		KeyNum = Key();
		if(KeyNum)
		{
			Temp = KeyNum;
		}
		Nixie(1, Temp);
		Delay(5);
	}
}

void Timer0_Routine(void) interrupt 1
{
	static unsigned int cnt = 0;

	TL0 = 0x18;
	TH0 = 0xFC;

	cnt++;
	if(cnt >= 20)
	{
		cnt = 0;
		Key_Loop();
	}
}
