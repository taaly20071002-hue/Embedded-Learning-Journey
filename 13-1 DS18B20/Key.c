#include <REGX52.H>

/* 独立按键(实测引脚):K1=P3.1  K2=P3.0  K3=P3.2  K4=P3.3 */

unsigned char Key(void)
{
	static unsigned char LastKey = 0;	/* 上次按键状态(消抖用)*/
	unsigned char NowKey = 0;

	/* 读当前按下的键 */
	if(P3_1 == 0) NowKey = 1;
	if(P3_0 == 0) NowKey = 2;
	if(P3_2 == 0) NowKey = 3;
	if(P3_3 == 0) NowKey = 4;

	/* 只在"从未按到按下"的瞬间返回键值(防止一次按键触发多次)*/
	if(NowKey != 0 && LastKey == 0)
	{
		LastKey = NowKey;
		return NowKey;
	}

	if(NowKey == 0)
	{
		LastKey = 0;					/* 松开,清状态 */
	}

	return 0;
}
