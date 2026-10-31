/* ============================================================
   蜂鸣器引脚探测 —— 找出你板子上蜂鸣器到底接哪个脚
   现象:如果引脚对 → 会持续"嘀——"响
        如果引脚不对 → 完全没声音
   ============================================================ */
#include <REGX52.H>
#include "Delay.h"
#include "Key.h"
#include "Nixie.h"
#include "Buzzer.h"
sbit Buzzer = P2^5;	

	/* ★ 先试 P2.5(江协科技标准接法)*/

unsigned char KeyNum;
void main()
{
	Nixie(1,0);

	while(1)
	{
		KeyNum = Key();
		
		if(KeyNum)
		{
			 Buzzer_Time(60);
		
		Nixie(1,KeyNum);
		}
		/* 1ms 翻转 → 500Hz 方波,能听见 */
	}
}
