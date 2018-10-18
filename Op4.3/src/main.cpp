// seting up baud rate, enige ding die mist van het boek. hier gevonden: https://www.avrfreaks.net/forum/setting-avr-baud-rates-c . een beetje aanpassing nodig
#define BAUD 9600

#include "util/setbaud.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//
uint8_t  dutyCycle = 255;
uint8_t  dutyCycleHigh = 255; // 255 == led is on
uint8_t  dutyCycleLow = 0; // 255 == led is on
uint8_t counter = 0;

void initLed(){
  DDRB = 0xff;
  DDRD = 0xff;
  PORTD = 0xff;
  PORTB |= (1<< 3);
}



//USART FUNCTIONS
void initUSART(void) {
  /* requires BAUD */
  UBRR0H = UBRRH_VALUE; /* defined in setbaud.h */
  UBRR0L = UBRRL_VALUE;
#if USE_2X
  UCSR0A |= (1 << U2X0);
#else
  UCSR0A &= ~(1 << U2X0);
#endif


 /* Enable USART transmitter/receiver */
 UCSR0B = (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0); // settup intterupt
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


// PWM FUNCTIONSS

static inline void initLedTimers(void){
  // Timer 0
	TCCR0A |= (1 << WGM20) | (1 << WGM21) | (1 << COM0A1) | (1 << COM0B1) ;//WGM20 | WGM21 = turning on 2 bits in the register to setup pwm mode / COM0A1 COM0B1 = setting up ping to switch when comparator reached
	TCCR0B |= (1 << CS11); /* PWM Freq = F_CPU/8/256(Setting up frequency) */


	// Timer 2
	TCCR2A|= (1 << WGM20) | (1 << WGM21) | (1 << COM2A1) ;//WGM20 | WGM21 = turning on 2 bits in the register to setup pwm mode / COM2A1 = setting up ping to switch when comparator reached
	TCCR2B |= (1 << CS21); /* PWM Freq = F_CPU/8/256(Setting up frequency) */


  //SET ALL LEDS LOW
  OCR0A = dutyCycleHigh;
  OCR0B = dutyCycleHigh;
  OCR2A = dutyCycleHigh;



}

/*static inline void initTimers(void) {
  TCCR1B |= (1 << CS11); // set clockspeed timer
  TIMSK1 |= (1 << TOIE1); // Enable timer intterupt


  //   TIMER0_OVF_vect |  TIMER0_COMPB_vect instead of overflow, when timer reaches comparator
}*/

ISR(USART_RX_vect){

  //Set brightness
  volatile char message = receiveByte();

  // set which light is on
  if(message == 'r')
  {
    OCR0B = dutyCycleLow;
    OCR0A = dutyCycleHigh;
    OCR2A = dutyCycleHigh;
    printString("Red \n");
  }
  else if(message == 'g'){
    OCR0B = dutyCycleHigh;
    OCR0A = dutyCycleLow;
    OCR2A = dutyCycleHigh;
    printString("Green \n");
  }
  else if(message == 'b'){
    OCR0B = dutyCycleHigh;
    OCR0A = dutyCycleHigh;
    OCR2A = dutyCycleLow;
    printString("Blue \n");
  }
  else{
    printString("wrong input \n");
  }


}



void opstelling(){
  initUSART();
  initLed();
  initLedTimers();
  sei();
  printString("Starting \n");
}


// Main function so program can run
int main(void){

    // Run code that only needs to be run once (setup)
    opstelling();

    // Same as Loop() in adruino. Infite loop while 1.
    while(1){

    }// Return 0 cause main is int
    return 0;
}
