/*
 * source.c
 *
 *  Created on: Sep 12, 2022
 *      Author: Mohamed Nabil
 */


#include "./../headerFiles/header.h"

void initSevenSegment(void){
	// determine the direction of the first 4 bits in port c as output
	DDRC |= 0x0F;
	// initialize it with zero
	PORTC = (PORTC&0xF0);
	//initialize the direction of the 6 bits in port A as output
	DDRA |= 0x3F;
	//initialize it with zero
	PORTA &= 0xC0;
}


void initTimer1_compareMode(void){
	TCCR1A = (1<<FOC1A);
	TCCR1B = (1<<CS10)|(1<<CS12)|(1<<WGM12);
	TCNT1 = 0;
	OCR1A = 977;
	TIMSK |= (1<<OCIE1A);
	SREG  |= (1<<7);
}

void initInterrupt0_1_2(void)
{
	//make interrupt 1 raising edge and interrupt 0 falling edge
	MCUCR = (MCUCR&0xF0)|(0x0E);
	//make interrupt 2 falling edge
	MCUCSR &= ~(1<<ISC2);
	//enable the three interrupts
	GICR |= 0xE0;
	//enable pull up by making PUD = 0
	SFIOR &= ~(1<<PUD);
	//make the bins in the ports as inputs
	DDRB &= ~(1<<PB2);
	DDRD &= 0xF3;
	//make the interrupt 0 and 2 internal pull up
	PORTB |= (1<<PB2);
	PORTD |= (1<<PD2);
}

ISR(TIMER1_COMPA_vect)
{
	if(seconds==59)
	{
		if(minutes==59)
		{
			hours++;
			minutes = 0;
		}
		else
		{
				minutes++;
		}
		seconds = 0;
	}
	else{
		seconds++;
	}
}

ISR(INT0_vect)
{
	//[edited : to have more function if this have been pressed two seconds will switch to the timer mode]
	seconds = minutes = hours = 0;
}
ISR(INT1_vect)
{
	//to pause the stop watch we will stop the timer interrupt
	TCCR1B &= ~((1<<CS10)|(1<<CS12));
	TIMSK &= ~(1<<OCIE1A);
	TCNT1 = 0;
}
ISR(INT2_vect)
{
	TCCR1B |= (1<<CS10)|(1<<CS12);
	TIMSK |= (1<<OCIE1A);
}
