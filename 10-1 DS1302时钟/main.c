/* ============================================================
   [10-2] DS1302 时钟 & 可调时钟
   功能:
     第一行显示 年-月-日
     第二行显示 时:分:秒
     K1:进入/切换设置项(年→月→日→时→分→秒→保存退出)
     K2:当前项 +1
     K3:当前项 -1
     设置时当前项闪烁
   ============================================================ */
#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "Key.h"

unsigned char KeyNum;
unsigned char MODE = 0;			/* 0=正常显示, 1~6=设置 年/月/日/时/分/秒 */
unsigned char FlashFlag = 0;	/* 闪烁标志 */
unsigned int  FlashTick = 0;	/* 闪烁计时 */

/* 各项的最大值:[0]年 [1]月 [2]日 [3]时 [4]分 [5]秒 */
unsigned char code TimeMax[7] = {99, 12, 31, 23, 59, 59, 6};

void DelayMs(unsigned int ms)
{
	unsigned char i, j;
	while(ms--)
	{
		i = 2;
		j = 239;
		do { while(--j); } while(--i);
	}
}

/* ============ 正常显示 ============ */
void TimeShow(void)
{
	DS1302_ReadTime();

	LCD_ShowNum(1, 1, DS1302_Time[0], 2);	/* 年 */
	LCD_ShowString(1, 3, "-");
	LCD_ShowNum(1, 4, DS1302_Time[1], 2);	/* 月 */
	LCD_ShowString(1, 6, "-");
	LCD_ShowNum(1, 7, DS1302_Time[2], 2);	/* 日 */

	LCD_ShowNum(2, 1, DS1302_Time[3], 2);	/* 时 */
	LCD_ShowString(2, 3, ":");
	LCD_ShowNum(2, 4, DS1302_Time[4], 2);	/* 分 */
	LCD_ShowString(2, 6, ":");
	LCD_ShowNum(2, 7, DS1302_Time[5], 2);	/* 秒 */
}

/* ============ 设置模式显示(当前项闪烁)============ */
void TimeSetShow(void)
{
	/* 年 */
	if(!(MODE == 1 && FlashFlag == 0))
		LCD_ShowNum(1, 1, DS1302_Time[0], 2);
	LCD_ShowString(1, 3, "-");
	/* 月 */
	if(!(MODE == 2 && FlashFlag == 0))
		LCD_ShowNum(1, 4, DS1302_Time[1], 2);
	LCD_ShowString(1, 6, "-");
	/* 日 */
	if(!(MODE == 3 && FlashFlag == 0))
		LCD_ShowNum(1, 7, DS1302_Time[2], 2);

	/* 时 */
	if(!(MODE == 4 && FlashFlag == 0))
		LCD_ShowNum(2, 1, DS1302_Time[3], 2);
	LCD_ShowString(2, 3, ":");
	/* 分 */
	if(!(MODE == 5 && FlashFlag == 0))
		LCD_ShowNum(2, 4, DS1302_Time[4], 2);
	LCD_ShowString(2, 6, ":");
	/* 秒 */
	if(!(MODE == 6 && FlashFlag == 0))
		LCD_ShowNum(2, 7, DS1302_Time[5], 2);
}

/* ============ 按键处理 ============ */
void TimeSet(void)
{
	if(KeyNum == 1)					/* K1:切换设置项 / 退出保存 */
	{
		MODE++;
		if(MODE > 6)
		{
			MODE = 0;
			DS1302_SetTime();		/* 退出设置 → 写入芯片 */
		}
		else
		{
			DS1302_ReadTime();		/* 进入设置 → 先读当前时间 */
		}
	}

	if(MODE != 0)
	{
		if(KeyNum == 2)				/* K2:加 */
		{
			DS1302_Time[MODE - 1]++;
			if(DS1302_Time[MODE - 1] > TimeMax[MODE - 1])
				DS1302_Time[MODE - 1] = 0;
		}
		if(KeyNum == 3)				/* K3:减 */
		{
			if(DS1302_Time[MODE - 1] == 0)
				DS1302_Time[MODE - 1] = TimeMax[MODE - 1];
			else
				DS1302_Time[MODE - 1]--;
		}
	}
}

void main()
{
	LCD_Init();
	DS1302_Init();

	DS1302_SetTime();		/* 首次上电写入初始时间(12:00:00)*/

	while(1)
	{
		KeyNum = Key();

		if(MODE == 0)
			TimeShow();			/* 正常显示 */
		else
			TimeSetShow();		/* 设置显示(闪烁)*/

		TimeSet();				/* 处理按键 */

		/* 闪烁计时:约 300ms 翻转一次 */
		FlashTick++;
		if(FlashTick >= 300)
		{
			FlashTick = 0;
			FlashFlag = !FlashFlag;
		}

		DelayMs(1);
	}
}
