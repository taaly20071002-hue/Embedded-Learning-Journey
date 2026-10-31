/* ============================================================
   [11-2] 蜂鸣器播放音乐
   ★ 如果你的蜂鸣器不在 P2.5,改下面这一行!
   ============================================================ */
#include <REGX52.H>
#include "Delay.h"
#include "Key.h"
#include "Timer0.h"

sbit Buzzer = P2^5;			/* ★ 改成你确认的蜂鸣器引脚 */

/* ===== 频率表:低音1~7, 中音1~7, 高音1~7(12MHz 晶振)===== */
unsigned int code FreqTable[] = {
	0,
	63628, 63731, 63835, 63928, 64021, 64103, 64185,	/* 低音 1~7 */
	64260, 64331, 64400, 64463, 64524, 64580, 64633,	/* 中音 1~7 */
	64684, 64732, 64777, 64820, 64860, 64898, 64934		/* 高音 1~7 */
};

/* ===== 乐谱:音符编号, 时值(单位:10ms)===== */
/* 两只老虎 */
unsigned char code Music[] = {
	5, 20,  6, 20,  8, 20,  6, 20,		/* 两只老虎 */
	5, 20,  6, 20,  5, 20,  3, 20,		/* 跑得快 */
	5, 20,  6, 20,  8, 20,  6, 20,		/* 两只老虎 */
	5, 20,  6, 20,  5, 20,  3, 20,		/* 跑得快 */
	5, 20,  6, 20,  8, 20,  6, 20,		/* 一只没有耳朵 */
	5, 20,  6, 20,  5, 20,  3, 20,		/* 一只没有尾巴 */
	5, 20,  6, 20,  8, 20,  6, 20,		/* 真奇怪 */
	5, 20,  6, 20,  5, 20,  3, 20,		/* 真奇怪 */
	0, 20,								/* 休止符 */
	0xFF								/* 结束标志 */
};

unsigned char FreqSelect;	/* 当前音符的频率对应索引 */
unsigned int  MusicSelect;	/* 乐谱索引 */
unsigned int  FreqValue;	/* 当前音符的定时器初值 */

void main()
{
	Timer0_Init();
	TR0 = 0;				/* 先不发声 */

	while(1)
	{
		if(Music[MusicSelect] != 0xFF)			/* 还没结束 */
		{
			FreqSelect = Music[MusicSelect];	/* 取音符 */
			MusicSelect++;

			if(FreqSelect != 0)					/* 不是休止符 */
			{
				FreqValue = FreqTable[FreqSelect];	/* 查频率表 */
				TR0 = 1;						/* 开始发声 */
			}
			else
			{
				TR0 = 0;						/* 休止符:停 */
			}

			Delay(10 * Music[MusicSelect]);		/* 按"时值"延时 */
			MusicSelect++;
		}
		else
		{
			MusicSelect = 0;					/* 播完重头开始 */
			TR0 = 0;
			Delay(500);
		}
	}
}

/* ===== 定时器0中断:产生音符频率 ===== */
void Timer0_Routine(void) interrupt 1
{
	TL0 = FreqValue % 256;
	TH0 = FreqValue / 256;
	Buzzer = !Buzzer;			/* 每半个周期翻转一次 → 方波 */
}
