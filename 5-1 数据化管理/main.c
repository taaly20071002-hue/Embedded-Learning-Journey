#include <REGX52.H>
#include "Delay.h"
#include "Nixie.h"
void main()
{
	while(1)
	{
	P2_1 = 0;
	Delay(500);
		P2_1 = 1;
		Delay(500);
		Nixie(2,3);
		Delay(500);
		Nixie(3,4);
		
	}

}