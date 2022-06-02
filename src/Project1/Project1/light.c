/*
 * light.c
 *
 * Created: 24-05-2022 17:01:22
 *  Author: ffsta
 */ 

#include "light.h"
#include <avr/io.h>
#define MAX 65535


void lightInitiate()
{
	DDRE = 0b00011000; //PE4 og PE3 sættes som output
	TCCR3B |= 1; //Ingen prescale
	TCCR3A |= 0b11; //PWM MODE 3
	TCCR3A |= 0b10100000; 
	TCCR3A &= 0b10101111; //Slukket imens timeren kører op og slukket imens den kører ned

	OCR3A = 0; //Slukket
	OCR3B = 0; //Slukket
}

void turnOnLight() {
	OCR3A = 500; //Timer til forlys (pin 5)
	OCR3B = 50000; //Timer til baglys (pin 2)
}

void turnOffLight() {
	OCR3A = 0; //Sluk
	OCR3B = 0; //Sluk
}
void changeToBreakingLight(int intensity) {
	//Tjek om intensiteten ligger i et lovligt interval
	if(intensity >= 0 && intensity <= MAX) { 
		OCR3B = intensity; //Sæt lysstyrken på baglyset til den givne parameter
	}
}
