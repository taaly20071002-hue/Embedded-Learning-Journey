#include <REGX52.H>
#include <Delay.h>
/* 独立按键:K1=P3.2  K2=P3.3  K3=P3.4  K4=P3.5 */
unsigned char Key(void)
{
	unsigned char KeyNumber = 0;

	if(P3_1 == 0) { while(P3_1 == 0);KeyNumber = 1; }
	if(P3_0 == 0) { while(P3_0 == 0);KeyNumber = 2; }
	if(P3_2 == 0) { while(P3_2 == 0);KeyNumber = 3; }
	if(P3_3 == 0) {while(P3_3== 0); KeyNumber = 4; }

	return KeyNumber;
}
