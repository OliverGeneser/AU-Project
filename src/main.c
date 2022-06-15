/********************************************
* MSYS, LAB 13. Part 2                      *
* ADC using "Start on Timer 1 overflow".    *
* Also using ADC interrupts.                *
*                                           *
* Henning Hargaard 11/4 2019                *
*********************************************/
#include <avr/io.h>

int main()
{
unsigned char i = 0;

  DDRA = 0xFF; //port A as output
  DDRB = 0xFF; //port B as output
  DDRC = 0xFF; //port C as output
  PORTA = 0xAA;
  while (1)
  {
    PORTC = PORTC ^ 0b00000001; //toggle PORTC.0
    PORTB = i;
    i++;
  }
}