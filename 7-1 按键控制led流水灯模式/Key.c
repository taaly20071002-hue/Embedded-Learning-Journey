/* ============================================================
   Key.c  —  独立按键驱动(适配普中开发板)
   接法: K1=P3.2  K2=P3.3  K3=P3.4  K4=P3.5
   返回: 1~4 对应 K1~K4;  0 = 没有按键
   ============================================================ */
#include <REGX52.H>
#include <Delay.H>

unsigned char Key()
{
	unsigned char KeyNumber = 0;

	if (P3_2 == 0) { Delay(20); while (P3_2 == 0); Delay(20); KeyNumber = 1; }  /* K1 */
	if (P3_3 == 0) { Delay(20); while (P3_3 == 0); Delay(20); KeyNumber = 2; }  /* K2 */
	if (P3_4 == 0) { Delay(20); while (P3_4 == 0); Delay(20); KeyNumber = 3; }  /* K3 */
	if (P3_5 == 0) { Delay(20); while (P3_5 == 0); Delay(20); KeyNumber = 4; }  /* K4 */

	return KeyNumber;
}
