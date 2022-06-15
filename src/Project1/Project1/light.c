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
	DDRH = 0xFF; //PH3 og PH4 sættes som output
	TCCR4B |= 1; //Ingen prescale
	TCCR4A |= 0b11; //PWM MODE 3
	TCCR4A |= 0b10100000; 
	TCCR4A &= 0b10101111; //Slukket imens timeren kører op og slukket imens den kører ned

	OCR4A = 0; //Slukket
	OCR4A = 0; //Slukket
}

void turnOnLight() {
	OCR4A = 500; //Timer til forlys (pin 5)
	OCR4B = 50000; //Timer til baglys (pin 2)
}

void turnOffLight() {
	OCR4A = 0; //Sluk
	OCR4B = 0; //Sluk
}
void changeToBreakingLight(int intensity) {
	//Tjek om intensiteten ligger i et lovligt interval
	if(intensity >= 0 && intensity <= MAX) { 
		OCR4B = intensity; //Sæt lysstyrken på baglyset til den givne parameter
	}
}
