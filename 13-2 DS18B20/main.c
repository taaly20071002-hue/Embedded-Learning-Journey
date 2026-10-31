#include <REGX52.H>
#include "DS18B20.h"
#include "LCD1602.h"
#include "Key.h"
#include "Delay.h"
#include "AT24C02.h"

float T;
char TLow,THigh; 
unsigned char KeyNum;
void main()
{
		LCD_Init();
		LCD_ShowString(1,1,"T:");
	LCD_ShowString(2,1,"TH");
	LCD_ShowString(2,9,"TL");
	LCD_ShowSignedNum(2,4,THigh,3);
			LCD_ShowSignedNum(2,12,TLow,3);
		while(1)
		{
					KeyNum = Key();
					DS18B20_ConvertT();
					T = DS18B20_ReadT();
			if(T<0)
			{
					LCD_ShowChar(1,3,'-');
				T= -T;
			}
			else
			{
					LCD_ShowChar(1,3,'+');
			}
			LCD_ShowNum(1,4,T,3);
			LCD_ShowChar(1,7,'.');
			LCD_ShowNum(1,8,(unsigned long)(T*100)%100,2);
			
if(KeyNum)
		{
		if(KeyNum == 1)
		{
		THigh++;
			
		}
			if(KeyNum == 2)
		{
		THigh--;
		}
			if(KeyNum == 3)
		{
		TLow++;
		}
			if(KeyNum == 4)
		{
		TLow--;
		}
			LCD_ShowSignedNum(2,4,THigh,3);
			LCD_ShowSignedNum(2,12,TLow,3);
		}
		}
		
			
}