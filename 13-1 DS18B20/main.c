#include <REGX52.H>
#include "DS18B20.h"
#include "LCD1602.h"
#include "Key.h"
#include "Delay.h"

float T;
char THigh = 30;			/* 上限初值 30℃ */
char TLow  = 10;			/* 下限初值 10℃ */
unsigned char KeyNum;

void main()
{
	LCD_Init();
	LCD_ShowString(1, 1, "T:");
	LCD_ShowString(2, 1, "TH");
	LCD_ShowString(2, 9, "TL");
	LCD_ShowSignedNum(2, 4, THigh, 3);
	LCD_ShowSignedNum(2, 12, TLow, 3);

	while(1)
	{
		KeyNum = Key();

		/* ===== 按键处理(★ 必须在循环里!)===== */
		if(KeyNum)
		{
			if(KeyNum == 1) THigh++;		/* K1:上限 +1 */
			if(KeyNum == 2) THigh--;		/* K2:上限 -1 */
			if(KeyNum == 3) TLow++;			/* K3:下限 +1 */
			if(KeyNum == 4) TLow--;			/* K4:下限 -1 */

			LCD_ShowSignedNum(2, 4, THigh, 3);
			LCD_ShowSignedNum(2, 12, TLow, 3);
		}

		/* ===== 测温 + 显示 ===== */
		DS18B20_ConvertT();
		Delay(750);							/* 等转换完成 */
		T = DS18B20_ReadT();

		if(T < 0)
		{
			LCD_ShowChar(1, 3, '-');
			T = -T;
		}
		else
		{
			LCD_ShowChar(1, 3, '+');
		}

		LCD_ShowNum(1, 4, (unsigned int)T, 3);
		LCD_ShowChar(1, 7, '.');
		LCD_ShowNum(1, 8, (unsigned long)(T * 100) % 100, 2);
	}
}
