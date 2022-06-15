/*
 * Motor.c
 *
 * Created: 5/3/2022 8:52:21 AM
 *  Author: Algorithm (Oliver G.)
 */

#include <avr/io.h>
#include <stdbool.h>
#define F_CPU 16000000 // defines the clock frequency
#include <avr/interrupt.h>

#include "Motor.h"

// variables for controlling speed and direction
bool reverseDirection = false;
bool smoothing = false;
unsigned char currentSpeed = 0;
unsigned char newSpeed = 0;

// functions for initialization of the interrupts and I/O port B
void initMotor()
{
	sei();
	TIMSK3 |= 0b00000000; // no interrupts
	TCCR3A = 0b00000000;  // normal mode
	TCCR3B = 0b00000010;  // prescaler

	TCCR1A = 0b10100011;
	TCCR1B = 0b00000001;
	OCR1A = 0;
	OCR1B = 0;
}


ISR(TIMER3_OVF_vect)
{
	// check for smoothing flag or directly sets the speed
	if (smoothing)
	{
		if (newSpeed < currentSpeed)
		{
			currentSpeed -= 1;
		}
		else if (newSpeed > currentSpeed)
		{
			currentSpeed += 1;
		}
	}
	else
	{
		currentSpeed = newSpeed;
	}

	// sets the output based on the current direction
	if (!reverseDirection)
	{
		OCR1B = 0;
		OCR1A = currentSpeed * 4;
	}
	else
	{
		OCR1A = 0;
		OCR1B = currentSpeed * 4;
	}
	
	// stops timer interrupts
	if (currentSpeed == newSpeed)
	{
		TIMSK3 |= 0b00000000;
	}
}

// function sets the new speed, sets the smoothing flag and starts the interrupt
void setSpeed(unsigned char speed, bool smooth)
{
	newSpeed = speed;
	smoothing = smooth;
	TIMSK3 |= 0b00000001;
}

// function for switching the direction
void switchDirection()
{
	reverseDirection = !reverseDirection;
}

// function for unit testing the driver
void testMotor()
{
	DDRA = 0;
	DDRB = 0xFF;
	PORTB = 0;

	while (1)
	{
		if (~PINA & (1 << 0))
		{
			setSpeed(0, false); // 0% uden smoothing
		}
		if (~PINA & (1 << 1))
		{
			setSpeed(0, true); // 0% med smoothing
		}
		if (~PINA & (1 << 2))
		{
			setSpeed(128, false); // 50% uden smoothing
		}
		if (~PINA & (1 << 3))
		{
			setSpeed(128, true); // 50% med smoothing
		}
		if (~PINA & (1 << 4))
		{
			setSpeed(192, true); // 75% med smoothing
		}
		if (~PINA & (1 << 5))
		{
			setSpeed(255, false); // 100% uden smoothing
		}
		if (~PINA & (1 << 6))
		{
			setSpeed(255, true); // 100% med smoothing
		}
		if (~PINA & (1 << 7))
		{
			reverseDirection = true;
		}
		else
		{
			reverseDirection = false;
		}
	}
}