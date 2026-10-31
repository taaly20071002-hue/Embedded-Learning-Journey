#include <REGX52.H>
#include "I2C.h"

#define AT24C02_ADDRESS		0xA0		/* 写地址;读地址 = 0xA0 | 0x01 = 0xA1 */

void AT24C02_WriteByte(unsigned char WordAddress, unsigned char Data)
{
	I2C_Start();
	I2C_SendByte(AT24C02_ADDRESS);		/* 设备地址 + 写 */
	I2C_ReceiveAck();
	I2C_SendByte(WordAddress);			/* 要写的字地址 */
	I2C_ReceiveAck();
	I2C_SendByte(Data);					/* 要写入的数据 */
	I2C_ReceiveAck();
	I2C_Stop();
}

unsigned char AT24C02_ReadByte(unsigned char WordAddress)
{
	unsigned char Data = 0;

	I2C_Start();
	I2C_SendByte(AT24C02_ADDRESS);		/* ① 设备地址 + 写 */
	I2C_ReceiveAck();
	I2C_SendByte(WordAddress);			/* ② 告诉芯片要读哪个地址 */
	I2C_ReceiveAck();

	I2C_Start();						/* ③ 重复起始(切换成读) */
	I2C_SendByte(AT24C02_ADDRESS | 0x01);	/* ★ 设备地址 + 读(0xA1)*/
	I2C_ReceiveAck();

	Data = I2C_ReceiveByte();			/* ④ 读数据 */
	I2C_SendAck(1);						/* ⑤ 发非应答(表示不要了)*/
	I2C_Stop();

	return Data;						/* ★ 必须返回! */
}
