/* ============================================================
   波特率扫描测试 v2 —— 发可打印字符,文本模式也能看清!
   用法:串口助手【文本/ASCII 模式】,波特率 4800
         观察收到的字符:
             1 1 1 1 ... → 第1档 (0xF4, 4800 @11.0592MHz)
             2 2 2 2 ... → 第2档 (0xF3, 4800 @12MHz)
             3 3 3 3 ... → 第3档 (0xFA, 9600 @11.0592MHz)
             4 4 4 4 ... → 第4档 (0xE8, 2400 @11.0592MHz)
             5 5 5 5 ... → 第5档 (0xFD, 19200 @11.0592MHz)
             6 6 6 6 ... → 第6档 (0xFF, 57600 @11.0592MHz)
         LED(P2.0) 每闪一次 = 切换到下一档
   ============================================================ */
#include <REGX52.H>
#include "Delay.h"
#include "UART.h"

void SetBaud(unsigned char reload)
{
	PCON |= 0x80;			/* SMOD = 1 */
	SCON  = 0x50;			/* 模式1,8位UART */
	TMOD &= 0x0F;
	TMOD |= 0x20;			/* 定时器1模式2 */
	TH1 = reload;
	TL1 = reload;
	TR1 = 1;
}

void main()
{
	unsigned char code bauds[6] = {0xF4, 0xF3, 0xFA, 0xE8, 0xFD, 0xFF};
	unsigned char i, j;

	while(1)
	{
		for(i = 0; i < 6; i++)
		{
			SetBaud(bauds[i]);
			for(j = 0; j < 30; j++)
			{
				UART_SendByte('1' + i);		/* ★ 发 '1'~'6' 可打印字符 */
				Delay(30);
			}
			P2_0 = ~P2_0;					/* LED 闪 = 换档 */
			Delay(800);
		}
	}
}
