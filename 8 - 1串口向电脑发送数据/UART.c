#include <REGX52.H>
#include "Delay.h"

void Uart1_Init(void)	/* 4800bps @ 11.0592MHz */
{
	PCON |= 0x80;		/* SMOD = 1 */
	SCON  = 0x50;		/* 8?UART,???? */
	TMOD &= 0x0F;
	TMOD |= 0x20;		/* ???1,??2 */
	TL1 = 0xF4;
	TH1 = 0xF4;
	ET1 = 1;
	TR1 = 1;
	EA = 1;
	ES = 1;
}

void UART_SendByte(unsigned char Byte)
{
	SBUF = Byte;
	while (TI == 0);	/* ? TI(?? T1) */
	TI = 0;				/* ? =(?? ==) */
}


