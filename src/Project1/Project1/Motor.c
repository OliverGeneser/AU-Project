/*
 * Motor.c
 *
 * Created: 5/3/2022 8:52:21 AM
 *  Author: Algorithm (Oliver G.)
 */ 
#include <avr/io.h>
#include <stdbool.h>
#define F_CPU 16000000 //defines clock
#include <avr/interrupt.h>
#include "Motor.h"

bool reverseDirection = false;
bool smoothing = false;
unsigned char currentSpeed = 0;
unsigned char newSpeed = 0;

void initMotor(){
	DDRB = 0xFF;
	
	sei();
	TIMSK3 |= 0b00000000; //no interrupts
	TCCR3A = 0b00000000; //normal mode
	TCCR3B = 0b00000010; //prescaler
	
	TCCR1A = 0b10100011;
	TCCR1B = 0b00000001;
	OCR1A = 0;
	OCR1B = 0;
}

ISR(TIMER3_OVF_vect){
	//stops timer interrupts
	if (currentSpeed == newSpeed){
		TIMSK3 |= 0b00000000;
	}
	
	if (smoothing) {
		if (newSpeed < currentSpeed)
		{
			currentSpeed -= 1;
		} 
		else if (newSpeed > currentSpeed)
		{
			currentSpeed += 1;
		}
	}else{
		currentSpeed = newSpeed;
	}
	
	if (!reverseDirection)
	{
		OCR1B = 0;
		OCR1A = currentSpeed * 4;
	}
	else {
		OCR1A = 0;
		OCR1B = currentSpeed * 4;
	}
}

void setSpeed(unsigned char speed, bool smooth){
	
	newSpeed = speed;
	smoothing = smooth;
	TIMSK3 |= 0b00000001;
}
	
void switchDirection(){
	reverseDirection = !reverseDirection;
}

void testMotor(){
	DDRA = 0;

	PORTB = 0;

	while(1){

		if (~PINA & (1 << 0))
		{
			setSpeed(0,false); //0%
		}
		if (~PINA & (1 << 1))
		{
			setSpeed(64,false); //25%
		}
		if (~PINA & (1 << 2))
		{
			setSpeed(128,false); //50%
		}
		if (~PINA & (1 << 3))
		{
			setSpeed(192,false); //75%
		}
		if (~PINA & (1 << 4))
		{
			setSpeed(255,true); //100%
		}
		
		if (~PINA & (1 << 7))
		{
			reverseDirection = true;
		}
		else{
			reverseDirection = false;
		}
	}
}