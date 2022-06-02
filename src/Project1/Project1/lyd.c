/*
 * lyd.c
 *
 * Created: 16-05-2022 15:37:13
 *  Author: ffsta
 */ 
#include "lyd.h"
#include "uart.h"

const unsigned char soundStart = 0x7E; //Start karakter, skal ikke ændres
unsigned char soundCMD = 0x00; //Bestemmer hvilken operation der skal udføres
const unsigned char soundFeedback = 0x00; //Bestemmer om der skal sendes feedback tilbage
unsigned char soundPara1 = 0x00; //Første parameter af den specifikke kommand kode
unsigned char soundPara2 = 0x00; //Anden parameter af den specifikke kommand kode
unsigned char checkSum1, checkSum2; //Første og andet byte af checksum
const unsigned char soundEnd = 0xEF; //Slut karakter, skal ikke ændres

void InitSound() {
	InitUART(9600, 8); //Uart intialiseres med 9600 baud rate med 8 databit
	
	soundCMD = 0x09;
	soundPara2 = 0x02;
	sendAudio();
	
}

void playTune(unsigned char tune) {
		soundPara2 = tune;
		soundCMD = 0x03;
		sendAudio();			
}

void setVolume(unsigned char volume) {
	if (volume > 30 || volume < 0) { // Se om parameteren ligger indenfor et lovligt interval
		volume = 30;
	}
	soundCMD = 0x06;
	soundPara2 = volume;
	
	sendAudio();
}

void checkSum(){
	unsigned int sum = 0xFFFF-(soundCMD+soundFeedback+soundPara1+soundPara2)+1; //Checksum 16 bit gemmes i en variabel vha. formlen fra databladet
	
	checkSum2 = sum % 256; //Find de 8 mindst betydede cifre
	checkSum1 = (sum - checkSum2) / 256; //Find de 8 mest betydende cifre
}

void stopAudio() {
	soundCMD = 0x16;
	soundPara2 = 0x00; //Reset 2. soundparameter
	sendAudio();
}

void sendAudio() {
	// Sends a 1 byte code to the SOMO 8 times
	checkSum(); //Checksum kaldes for at finde de rigtige værdier til checksum1 og checksum2
	SendChar(soundStart);
	SendChar(soundCMD);
	SendChar(soundFeedback);
	SendChar(soundPara1);
	SendChar(soundPara2);
	SendChar(checkSum1);
	SendChar(checkSum2);
	SendChar(soundEnd);
}