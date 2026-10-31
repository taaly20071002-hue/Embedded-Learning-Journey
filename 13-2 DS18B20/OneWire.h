#ifndef __ONEWIRE__H_
#define __ONEWIRE__H_

unsigned char OneWire_Init(void); 
void OneWire_SendBit(unsigned char Bit);
unsigned char OneWire_ReceiveBit();
void OneWire_SendByte(unsigned char Byte);
unsigned char OneWire_ReceiveByte(void);
#endif