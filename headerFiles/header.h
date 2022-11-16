/*
 * header.h
 *
 *  Created on: Sep 12, 2022
 *      Author: Mohamed Nabil
 */

#ifndef HEADER_H_
#define HEADER_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
//functions
void initSevenSegment(void);
void initTimer1_compareMode(void);
void initInterrupt0(void);
//macros
#define display(num) PORTC=(PORTC&0xF0)|(num&0x0F)
#define enable(num) PORTA=(PORTA&0xC0)|num;
//variables
extern unsigned char seconds;
extern unsigned char minutes;
extern unsigned char hours;
#endif /* HEADER_H_ */
