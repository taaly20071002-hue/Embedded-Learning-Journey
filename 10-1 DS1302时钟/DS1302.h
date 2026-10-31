#ifndef __DS1302_H__
#define __DS1302_H__

/* 时间数组:[0]年 [1]月 [2]日 [3]时 [4]分 [5]秒 [6]星期 */
extern unsigned char DS1302_Time[7];

void DS1302_Init(void);
void DS1302_WriteByte(unsigned char Command, unsigned char Data);
unsigned char DS1302_ReadByte(unsigned char Command);
void DS1302_SetTime(void);		/* 把 DS1302_Time 写入芯片 */
void DS1302_ReadTime(void);		/* 从芯片读到 DS1302_Time */
unsigned char DS1302_Time[7];

#endif
