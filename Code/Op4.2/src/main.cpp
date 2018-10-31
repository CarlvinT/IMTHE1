// seting up baud rate, enige ding die mist van het boek. hier gevonden: https://www.avrfreaks.net/forum/setting-avr-baud-rates-c . een beetje aanpassing nodig
#define BAUD 9600
#include "util/setbaud.h"
#include <avr/io.h>
#include <util/delay.h>

//
void initLed(){
  DDRB = 0xff;
  DDRD = 0xff;
  PORTD = 0xff;
  PORTB |= (1<< 3);
}


//ALLES HIERONDER IS LETTERLIJK UIT HET BOEK


void initUSART(void) { /* requires BAUD */
  UBRR0H = UBRRH_VALUE; /* defined in setbaud.h */
  UBRR0L = UBRRL_VALUE;
#if USE_2X
  UCSR0A |= (1 << U2X0);
#else
  UCSR0A &= ~(1 << U2X0);
#endif


 /* Enable USART transmitter/receiver */
 UCSR0B = (1 << TXEN0) | (1 << RXEN0);
 UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); /* 8 data bits, 1 stop bit */
}

void transmitByte(uint8_t data) {
  /* Wait for empty transmit buffer */
  loop_until_bit_is_set(UCSR0A, UDRE0);
  UDR0 = data; /* send data */
}

uint8_t receiveByte(void) {
  loop_until_bit_is_set(UCSR0A, RXC0); /* Wait for incoming data */
  return UDR0; /* return register value */
}
// Example of a useful printing command
void printString(const char myString[]) {
  uint8_t i = 0;
  while (myString[i]) {
    transmitByte(myString[i]);
    i++;
 }
}


// EIND BOEK UITLEG.



void opstelling(){
  initUSART();
  initLed();
}


// Main function so program can run
int main(void){

    // Run code that only needs to be run once (setup)
    opstelling();

    // Same as Loop() in adruino. Infite loop while 1.
    while(1){

      // receive input
      char message = receiveByte();

      // check input and output appropriate action
      if (message == 'a'){
        PORTB ^= (1<<PB3);
        printString("Led is aan \n");
      }
      else if (message == 'u'){
        PORTB ^= (1<<PB3);
        printString("Led is uit \n");
      }
      else{
        printString("Wrong input \n");
      }

    }// Return 0 cause main is int
    return 0;
}
