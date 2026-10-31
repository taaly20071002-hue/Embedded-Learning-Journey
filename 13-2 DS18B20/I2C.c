#include <REGX52.H>

sbit I2C_SCL = P2^1;
sbit I2C_SDA = P2^0;

void I2C_Start()
{
		I2C_SDA = 1;
		I2C_SCL = 1;
		I2C_SDA = 0;
		I2C_SCL = 0;
}

void I2C_Stop()
{
		I2C_SDA = 0;
		I2C_SCL = 1;
		I2C_SDA = 1;
		
}
void I2C_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		I2C_SDA = Byte&(0x80>>i);
		I2C_SCL = 1;
		I2C_SCL = 0;
	}

}


unsigned char I2C_ReceiveByte()
{
		unsigned char Byte = 0x00;
		unsigned char i;
		I2C_SDA = 1;
		for(i=0;i<8;i++)
	{		
		I2C_SCL = 1;
		if(I2C_SDA){Byte |= (0x80>>i);}
		I2C_SCL = 0;
	}
		return Byte;
}

void I2C_SendAck(unsigned char AckBit)
{
		I2C_SDA = AckBit;
		I2C_SCL = 1;
		I2C_SCL = 0;
}

unsigned char I2C_ReceiveAck(void)
{
	unsigned char AckBit;
	I2C_SDA = 1;			/* 释放 SDA,让从机驱动 */
	I2C_SCL = 1;			/* SCL 拉高,从机在这时输出 ACK */
	AckBit = I2C_SDA;		/* 读 ACK 位 */
	I2C_SCL = 0;			/* 拉低 SCL,结束这一位 */
	return AckBit;
}