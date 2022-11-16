/*
 * main.c
 *
 *  Created on: Sep 12, 2022
 *      Author: Mohamed Nabil
 */

//will define here the time in seconds and minutes
unsigned char seconds = 0;
unsigned char minutes = 0;
unsigned char hours   = 0;

#include"./headerFiles/header.h"
int main(void)
{
	//initializations
	//[1] : seven segment
	initSevenSegment();
	//[2] : timer
	initTimer1_compareMode();
	//[3] : interrupts
	initInterrupt0_1_2();
	//main code
	while(1)
	{
		//the only code will while contain is display on seven segments
		enable(0x01);
		display(seconds%10);
		_delay_ms(2);
		enable(0x02);
		display(seconds/10);
		_delay_ms(2);
		enable(0x04);
		display(minutes%10);
		_delay_ms(2);
		enable(0x08);
		display(minutes/10);
		_delay_ms(2);
		enable(0x10);
		display(hours%10);
		_delay_ms(2);
		enable(0x20);
		display(hours/10);
		_delay_ms(2);
	}

}
