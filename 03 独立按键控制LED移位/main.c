
#include <REGX52.H>
void Delay(unsigned int xms)	//@12.000MHz
{
	unsigned char data i, j;
		while(xms--)
	{
	i = 2;
	j = 239;
	do
	{
		while (--j);
	} while (--i);
}
}

void main()
{
	unsigned char LedNum = -1;
    while(1)
		{
		if(P3_1 == 0)
		{
		Delay(20);
		while(P3_1 == 0);
		Delay(20);
			
		LedNum++;
		if(LedNum >= 8)
		{
		LedNum = -1;
		}
		P2 = ~(0x01<<LedNum);
		}
		}
}
