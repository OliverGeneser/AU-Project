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
#define F_CPU 16000000 // defines clock
#include <avr/interrupt.h>
#include <util/delay.h>

// includes drivers
#include "motor.h"
#include "lyd.h"
#include "light.h"

unsigned char triggers = 0;

// ISR on INT0
ISR(INT0_vect)
{
	// increments the current map number
	triggers++;

	// switch for controlling the car in relation to the current reflex
	switch (triggers)
	{
	case 0:
playTune(2);
		break;
	case 1:
		playTune(2);
		break;
	case 2:
		playTune(2);
		setSpeed(255, false);
		break;
	case 3:
		playTune(2);
		setSpeed(10, false);
		break;
	case 4:
		playTune(2);
		setSpeed(100, false);
		setSpeed(255, true);
		break;
	case 5:
		playTune(2);
		break;
	case 6:
		playTune(2);
		switchDirection();
		changeToBreakingLight(65535);
		setSpeed(30, false);
		
		setSpeed(200, true);
		changeToBreakingLight(10000);
		
		break;
	case 7:
		playTune(2);
		break;
	case 8:
		playTune(2);
		switchDirection();
		changeToBreakingLight(65535);
		setSpeed(030, false);
	
		
		
		setSpeed(180, true);
		changeToBreakingLight(10000);
		break;
		case 9:
		playTune(2);
		break;
		case 10:
		playTune(2);
		break;
	case 11:
		playTune(3);
		setSpeed(0, false);
		turnOffLight();
		break;
	
	default:
		break;
}
	// waits to avoid double triggers from left/right
	_delay_ms(250);
	EIFR = 0xFF;
	EIMSK |= 0b00000011;
}

// ISR on INT1
ISR(INT1_vect)
{
	triggers++;
	
		switch (triggers)
		{
			case 0:
			playTune(2);
			break;
			case 1:
			playTune(2);
			break;
			case 2:
			playTune(2);
			setSpeed(255, false);
			break;
			case 3:
			playTune(2);
			setSpeed(10, false);
			break;
			case 4:
			playTune(2);
			setSpeed(100, false);
			setSpeed(255, true);
			break;
			case 5:
			playTune(2);
			break;
			case 6:
			playTune(2);
			switchDirection();
			changeToBreakingLight(65535);
			setSpeed(30, false);
			
			setSpeed(200, true);
			changeToBreakingLight(10000);
			
			break;
			case 7:
			playTune(2);
			break;
			case 8:
			playTune(2);
			switchDirection();
			changeToBreakingLight(65535);
			setSpeed(030, false);
			
			
			
			setSpeed(180, true);
			changeToBreakingLight(10000);
			break;
			case 9:
			playTune(2);
			break;
			case 10:
			playTune(2);
			break;
			case 11:
			playTune(3);
			setSpeed(0, false);
			turnOffLight();
			break;
			
			default:
			break;
		}
	_delay_ms(250);

	EIFR = 0xFF;
	EIMSK |= 0b00000011;
}

int main(void)
{
	// initializing all software modules
	sei();
	initMotor();
	InitSound();
	lightInitiate();
	DDRB = 0xFF;
	DDRA = 0;

	EICRA = 0b00001111;

	setVolume(30);

	triggers = 0;
	while (1)
	{
		if (~PINA & (1 << 0))
		{
			EIMSK |= 0b00000011;
			// starts the car by playing the start sound and starting the lights
			turnOnLight();
			playTune(1);
			_delay_ms(2000);
			setSpeed(50, false);
			setSpeed(255, true);
		}
	}
}
