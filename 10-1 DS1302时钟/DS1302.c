#include <REGX52.H>

sbit DS1302_SCLK = P3^6;
sbit DS1302_IO   = P3^4;
sbit DS1302_CE   = P3^5;

/* 时间数组:[0]年 [1]月 [2]日 [3]时 [4]分 [5]秒 [6]星期 */
unsigned char DS1302_Time[7] = {23, 1, 1, 12, 0, 0, 1};

/* ===== BCD <-> 十进制 ===== */
unsigned char BCD2Dec(unsigned char BCD)
{
	return (BCD >> 4) * 10 + (BCD & 0x0F);
}

unsigned char Dec2BCD(unsigned char Dec)
{
	return ((Dec / 10) << 4) | (Dec % 10);
}

/* ===== 约 10us 延时 ===== */
void DS1302_Delay(void)
{
	unsigned char i;
	for(i = 0; i < 5; i++);
}

void DS1302_Init(void)
{
	DS1302_CE   = 0;
	DS1302_SCLK = 0;
	DS1302_IO   = 0;
}

void DS1302_WriteByte(unsigned char Command, unsigned char Data)
{
	unsigned char i;

	DS1302_CE = 1;
	DS1302_Delay();

	for(i = 0; i < 8; i++)			/* 发命令(低位在前)*/
	{
		DS1302_IO = Command & (0x01 << i);
		DS1302_Delay();
		DS1302_SCLK = 1;
		DS1302_Delay();
		DS1302_SCLK = 0;
		DS1302_Delay();
	}

	for(i = 0; i < 8; i++)			/* 发数据 */
	{
		DS1302_IO = Data & (0x01 << i);
		DS1302_Delay();
		DS1302_SCLK = 1;
		DS1302_Delay();
		DS1302_SCLK = 0;
		DS1302_Delay();
	}

	DS1302_CE = 0;
	DS1302_Delay();
}

unsigned char DS1302_ReadByte(unsigned char Command)
{
	unsigned char i;
	unsigned char Data = 0;

	Command |= 0x01;				/* 读命令 */
	DS1302_CE = 1;
	DS1302_Delay();

	for(i = 0; i < 8; i++)			/* 发命令 */
	{
		DS1302_IO = Command & (0x01 << i);
		DS1302_Delay();
		DS1302_SCLK = 1;
		DS1302_Delay();
		DS1302_SCLK = 0;
		DS1302_Delay();
	}

	DS1302_IO = 1;					/* 释放 IO 线 */
	DS1302_Delay();
	DS1302_Delay();

	for(i = 0; i < 8; i++)			/* 读数据 */
	{
		DS1302_SCLK = 1;
		DS1302_Delay();
		DS1302_SCLK = 0;
		DS1302_Delay();
		if(DS1302_IO)
		{
			Data |= (0x01 << i);
		}
		DS1302_Delay();
	}

	DS1302_CE = 0;
	DS1302_Delay();
	return Data;
}

/* ===== 把 DS1302_Time 数组写入芯片 ===== */
void DS1302_SetTime(void)
{
	DS1302_WriteByte(0x8E, 0x00);						/* 开锁 */
	DS1302_WriteByte(0x80, Dec2BCD(DS1302_Time[5]));	/* 秒 */
	DS1302_WriteByte(0x82, Dec2BCD(DS1302_Time[4]));	/* 分 */
	DS1302_WriteByte(0x84, Dec2BCD(DS1302_Time[3]));	/* 时 */
	DS1302_WriteByte(0x86, Dec2BCD(DS1302_Time[2]));	/* 日 */
	DS1302_WriteByte(0x88, Dec2BCD(DS1302_Time[1]));	/* 月 */
	DS1302_WriteByte(0x8A, Dec2BCD(DS1302_Time[6]));	/* 星期 */
	DS1302_WriteByte(0x8C, Dec2BCD(DS1302_Time[0]));	/* 年 */
	DS1302_WriteByte(0x8E, 0x80);						/* 上锁 */
}

/* ===== 从芯片读到 DS1302_Time 数组 ===== */
void DS1302_ReadTime(void)
{
	DS1302_Time[5] = BCD2Dec(DS1302_ReadByte(0x81) & 0x7F);	/* 秒(屏蔽 CH)*/
	DS1302_Time[4] = BCD2Dec(DS1302_ReadByte(0x83));			/* 分 */
	DS1302_Time[3] = BCD2Dec(DS1302_ReadByte(0x85) & 0x3F);	/* 时(屏蔽 bit7/bit5)*/
	DS1302_Time[2] = BCD2Dec(DS1302_ReadByte(0x87));			/* 日 */
	DS1302_Time[1] = BCD2Dec(DS1302_ReadByte(0x89));			/* 月 */
	DS1302_Time[6] = BCD2Dec(DS1302_ReadByte(0x8B));			/* 星期 */
	DS1302_Time[0] = BCD2Dec(DS1302_ReadByte(0x8D));			/* 年 */
}
