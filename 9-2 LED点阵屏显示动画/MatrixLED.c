#include <REGX52.H>
#include "Delay.h"

sbit RCK = P3^5;	/* RCLK 锁存时钟 */
sbit SCK = P3^6;	/* SCLK 移位时钟 */
sbit SER = P3^4;	/* 串行数据 */

void _74HC595_WriteByte(unsigned char Byte)
{
	unsigned char i;
	for(i = 0; i < 8; i++)
	{
		SER = Byte & (0x80 >> i);
		SCK = 1;
		SCK = 0;
	}
	RCK = 1;
	RCK = 0;
}

void MatrixLED_ShowColumn(unsigned char column, unsigned char Data)
{
	_74HC595_WriteByte(Data);
	P0 = ~(0x80 >> column);		/* 选中第 column 列 */
	Delay(1);					/* 显示 1ms */
	P0 = 0xFF;					/* ★ 消影:关闭所有列,防止拖影 */
}

void MatrixLED_Init()
{
	SCK = 0;
	RCK = 0;
}
