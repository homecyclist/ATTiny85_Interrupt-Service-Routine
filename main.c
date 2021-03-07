/*
 * Timer Example
 * 
 * This example will set timer0 and timer1 to call ISR vector
 *
 */
#include <xc.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000

void timer0_init(void)
{
	/*
	This timer will fire ISR(TIMER0_COMPA_vect) on match.
	*/
	TCCR0A = (1<<WGM01);     //CTC mode. Count until OCR0A, then reset.
	TCCR0B = (3<<CS00);      //F_CPU / 64
	OCR0A  = 249;			 //1 ms
	TIMSK |= (1<<OCIE0A);    //Call ISR(TIMER0_COMPA_vect) on match
}

void timer1_init(void)
{
	/*
	This timer will fire ISR(TIMER1_COMPA_vect) on match.
	*/
	TCCR1 |= (1<<CTC1);		//CTC mode. Count until OCR1C, then reset
	TCCR1 |= (8<<CS10);		//F_CPU / 64
	OCR1C = 124;			//1 ms
	TIMSK |= (1<<OCIE1A);	//Call ISR(TIMER1_COMPA_vect) on match
}

int main(void)
{
	DDRB = (1<<DDB4) | (1<<DDB3);
	timer0_init();
	timer1_init();
    sei ();        // allow interrupts
    while(1) 
	{
	// Nothing is needed here!
	}  

}

ISR(TIMER0_COMPA_vect)
{
	// toggle pin 3
	PORTB ^= (1<<PB4);   
}

ISR(TIMER1_COMPA_vect)
{
	// toggle pin 4
	PORTB ^= (1<<PB3); 
}