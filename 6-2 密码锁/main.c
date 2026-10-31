#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "MatrixKey.h"

void main()
{
	unsigned char KeyNum;
	unsigned int  password = 0;          /* ★ 必须初始化为 0 */
   unsigned int cnt = 0;
	unsigned int sb;
	LCD_Init();
	LCD_ShowString(1, 1, "Password:");   /* 第一行:标题 */

	while (1)
	{
		KeyNum = MatrixKey();
		if (KeyNum)
		{
			if (KeyNum <= 10)
			{
				if(cnt < 4){
				password = password*10;
				password = password + KeyNum%10;
				cnt++;
		}
				  /* 第5列开始显示密码 */
			}
		LCD_ShowNum(2,2, password, 4); 
}
}
	}