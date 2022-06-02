/*
 * Project1.c
 *
 * Created: 5/3/2022 8:49:58 AM
 * Author : Algorithm (Oliver G.)
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define F_CPU 16000000 //defines clock
#include <avr/interrupt.h>
#include <util/delay.h>

#include "motor.h"
#include "lyd.h"
#include "light.h"

unsigned char triggers = 0;

ISR(INT0_vect){
	EIMSK |= 0b00000000;
	
	triggers++;
	
	switch(triggers){
		case 0:
			break;
		case 1:
			playTune(2);
			break;
		case 2:
			playTune(2);
			setSpeed(255,false);
			break;
		case 3:
			playTune(2);
			setSpeed(10,false);
			break;
		case 4:
			playTune(2);
			setSpeed(100,false);
			setSpeed(255,true);
			break;
		case 6:
			playTune(2);
			setSpeed(0,false);
			switchDirection();
			setSpeed(200,true);
			break;
		case 8:
			playTune(2);
			setSpeed(0,false);
			switchDirection();
			setSpeed(180,true);
			break;
		case 11:
			playTune(3);
			setSpeed(0,false);
			break;
	}
	_delay_ms(500);
	EIFR = 0xFF;
	EIMSK |= 0b00000011;
}
ISR(INT1_vect){
	EIMSK |= 0b00000000;
	
	triggers++;
	switch(triggers){
		case 0:
			break;
		case 1:
			playTune(2);
			break;
		case 2:
			playTune(2);
			setSpeed(255,false);
			break;
		case 3:
			playTune(2);
			setSpeed(10,false);
			break;
		case 4:
			playTune(2);
			setSpeed(100,false);
			setSpeed(255,true);
			break;
		case 6:
			playTune(2);
			setSpeed(0,false);
			switchDirection();
			setSpeed(200,true);
			break;
		case 8:
			playTune(2);
			setSpeed(0,false);
			switchDirection();
			setSpeed(180,true);
			break;
		case 11:
			playTune(3);
			setSpeed(0,false);
			break;

	}
	_delay_ms(500);
	
	EIFR = 0xFF;
	EIMSK |= 0b00000011;
}


int main(void)
{
	sei();
	initMotor();
	InitSound();
	lightInitiate();
	DDRB = 0xFF;
	DDRA = 0;

	EICRA = 0b00001111;
	
	setVolume(30);
	
	//testMotor();
    triggers = 0;
	
	/* Replace with your application code */
    while (1) 
    {	
			if (~PINA & (1 << 0))
			{
				playTune(1);
				setSpeed(50,false);
				setSpeed(255,true);
			}
		//testMotor();
		
	}
}

