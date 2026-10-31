#include <REGX52.H>

sbit OneWire_DQ = P3^7;		/* DS18B20 数据线 */

/* ===== 初始化(复位脉冲 + 检测存在脉冲)===== */
unsigned char OneWire_Init(void)
{
	unsigned char i;
	unsigned char AckBit;

	OneWire_DQ = 1;
	OneWire_DQ = 0;				/* 拉低总线 */
	i = 247; while (--i);		/* 延时约 500us(复位脉冲)*/
	OneWire_DQ = 1;				/* 释放总线 */
	i = 32;  while (--i);		/* 等待约 70us */
	AckBit = OneWire_DQ;		/* 读存在脉冲(0=有器件)*/
	i = 247; while (--i);		/* 等待 500us */

	return AckBit;
}

/* ===== 发送一位 ===== */
void OneWire_SendBit(unsigned char Bit)
{
	unsigned char i;

	OneWire_DQ = 0;
	i = 4;  while (--i);		/* 拉低约 10us */
	OneWire_DQ = Bit;			/* 写入数据位 */
	i = 24; while (--i);		/* 保持约 50us */
	OneWire_DQ = 1;				/* ★ 释放总线(原来是 0,错误!) */
}

/* ===== 接收一位 ===== */
unsigned char OneWire_ReceiveBit(void)
{
	unsigned char Bit;
	unsigned char i;

	OneWire_DQ = 0;
	i = 2;  while (--i);		/* 拉低约 5us(启动读时隙)*/
	OneWire_DQ = 1;				/* 释放总线 */
	i = 2;  while (--i);		/* 等待约 5us */
	Bit = OneWire_DQ;			/* 读数据位 */
	i = 24; while (--i);		/* 等待 50us */

	return Bit;
}

/* ===== 发送一个字节(低位在前)===== */
void OneWire_SendByte(unsigned char Byte)
{
	unsigned char i;

	for(i = 0; i < 8; i++)		/* ★ 补上 i++(原来死循环!)*/
	{
		OneWire_SendBit(Byte & (0x01 << i));
	}
}

/* ===== 接收一个字节 ===== */
unsigned char OneWire_ReceiveByte(void)
{
	unsigned char i;
	unsigned char Byte = 0x00;

	for(i = 0; i < 8; i++)		/* ★ 补上 i++ */
	{
		if(OneWire_ReceiveBit())	/* ★ 接收一位(原来是 SendByte)*/
		{
			Byte |= (0x01 << i);
		}
	}

	return Byte;
}
