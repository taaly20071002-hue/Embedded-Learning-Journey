#include <REGX52.H>

/* ★ 实测确认的引脚(江协科技标准接法):
      K1 = P3.1
      K2 = P3.0
      K3 = P3.2
      K4 = P3.3                                 */

unsigned char Key_KeyNumber;

/* ===== 读键值(读一次清一次)===== */
unsigned char Key(void)
{
	unsigned char Temp;
	Temp = Key_KeyNumber;
	Key_KeyNumber = 0;
	return Temp;
}

/* ===== 读取按键原始状态 ===== */
unsigned char Key_GetState(void)
{
	unsigned char KeyNumber = 0;

	if(P3_1 == 0) { KeyNumber = 1; }	/* K1 */
	if(P3_0 == 0) { KeyNumber = 2; }	/* K2 */
	if(P3_2 == 0) { KeyNumber = 3; }	/* K3 */
	if(P3_3 == 0) { KeyNumber = 4; }	/* K4 */

	return KeyNumber;
}

/* ===== 定时扫描(每 20ms 调用一次)===== */
void Key_Loop(void)
{
	static unsigned char LastData = 0;
	unsigned char NowData;

	NowData = Key_GetState();

	if(LastData != 0 && NowData == 0)	/* 上次按下,这次松开 → 触发 */
	{
		Key_KeyNumber = LastData;
	}

	LastData = NowData;
}
