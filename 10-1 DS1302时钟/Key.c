#include <REGX52.H>

/* 独立按键:K1=P3.2  K2=P3.3  K3=P3.4  K4=P3.5 */
unsigned char Key(void)
{
	unsigned char KeyNumber = 0;

	if(P3_2 == 0) { KeyNumber = 1; }
	if(P3_3 == 0) { KeyNumber = 2; }
	if(P3_4 == 0) { KeyNumber = 3; }
	if(P3_5 == 0) { KeyNumber = 4; }

	return KeyNumber;
}
