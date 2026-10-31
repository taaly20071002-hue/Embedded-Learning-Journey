#include <REGX52.H>
#include <Timer0.H>
#include <Key.H>
#include <INTRINS.H>
unsigned char LMODE = 0;

void main()
{
	unsigned char KeyNum;
	P2 = 0xEF;
	Timer0_Init();
	while(1)
	{
			KeyNum = Key();
		if(KeyNum)
		{
		if(KeyNum == 1)
		{
		LMODE++;
			if(LMODE >= 2)
			{
			LMODE = 0;
			}
		}
			

		}
	}
}
void Timer0_Routine() interrupt 1
{
	static unsigned int cnt = 0;
		TL0 = 0x18;				//???????
	   TH0 = 0xFC;
		cnt++;
	if(cnt >= 500)
	{
	cnt = 0;
		if(LMODE == 0)
		{
			P2 =_crol_(P2,1);
		}
		if(LMODE == 1)
		{
			P2 =_cror_(P2,1);
		}

	}
}
