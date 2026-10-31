#include <REGX52.H>

void Timer0_Init(void)
{
	TMOD &= 0xF0;
	TMOD |= 0x01;			/* 定时器0,16位模式 */
	TF0 = 0;
	TR0 = 1;
	ET0 = 1;
	EA  = 1;
	PT0 = 0;
}
