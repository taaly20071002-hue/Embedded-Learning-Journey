#include <REGX52.H>
#include <LCD1602.h>
#include	<Delay.h>
#include  <Timer0.h>
unsigned char Sec;
void main()
{
	LCD_Init();
	Timer0_Init();
	LCD_ShowString(1,1,"Clock:");
		while(1)
		{
     LCD_ShowNum(2,1,Sec,2);
			
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
		Sec++;
	};
}