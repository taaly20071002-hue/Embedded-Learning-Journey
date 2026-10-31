#include <STC8051U.H>

#include <INTRINS.H>
void Delay500ms(void)	//@12.000MHz
{
	unsigned char data i, j, k;

	_nop_();
	i = 4;
	j = 205;
	k = 187;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
void main()
{
	while(1)
	{
		P2 = 0xFF;
		Delay500ms();
		P2 = 0XFE;
		Delay500ms();
	}
}