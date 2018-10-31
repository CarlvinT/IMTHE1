#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/*
TCNTn = internal timer / counter register
OCRn = Output compare register

Timer 0: 8-bit, PWM on chip pins 11 and 12
Timer 1: 16-bit, PWM on chip pins 15 and 16
Timer 2: 8-bit, PWM on chip pins 17 and 5

http://www.avrbeginners.net/architecture/timers/timers.html#tcnt
https://www.avrfreaks.net/forum/tut-c-newbies-guide-avr-timers?name=PNphpBB2&file=viewtopic&t=50106
https://www.mikrocontroller.net/attachment/136731/Timer_Register_ATmega8_und_ATmega88.pdf
https://www.arduino.cc/en/Tutorial/SecretsOfArduinoPWM

D5 = red
D6 = green
D11 = blue

*/

uint8_t  dutyCycle = 255;
uint8_t  dutyCycleLow = 255;
uint8_t counter = 0;


void initLed(){
  DDRB = 0xff;
  DDRD = 0xff;
  PORTB = 0x00;
  PORTD = 0x00;
}

static inline void initLedTimers(void){
  // Timer 0
	TCCR0A |= (1 << WGM20) | (1 << WGM21) | (1 << COM0A1) | (1 << COM0B1) ;//WGM20 | WGM21 = turning on 2 bits in the register to setup pwm mode / COM0A1 COM0B1 = setting up ping to switch when comparator reached
	TCCR0B |= (1 << CS11); /* PWM Freq = F_CPU/8/256(Setting up frequency) */


	// Timer 2
	TCCR2A|= (1 << WGM20) | (1 << WGM21) | (1 << COM2A1) ;//WGM20 | WGM21 = turning on 2 bits in the register to setup pwm mode / COM2A1 = setting up ping to switch when comparator reached
	TCCR2B |= (1 << CS21); /* PWM Freq = F_CPU/8/256(Setting up frequency) */


  //SET ALL LEDS LOW
  OCR0A = dutyCycleLow;
  OCR0B = dutyCycleLow;
  OCR2A = dutyCycleLow;



}

static inline void initTimers(void) {
  TCCR1B |= (1 << CS11); // set clockspeed timer
  TIMSK1 |= (1 << TOIE1); // Enable timer intterupt


  //   TIMER0_OVF_vect |  TIMER0_COMPB_vect instead of overflow, when timer reaches comparator
}

void opstelling(){

  initLed();
  initTimers();
  initLedTimers();
  sei();

}

// Interrupt service routine when timer overflows.
ISR(TIMER1_OVF_vect){

  //Set brightness
  if(dutyCycle == 0){
    dutyCycle = 255;
    counter += 1;
  }
  else{
    dutyCycle -= 1;
  }

  // set which light is on
  if(counter == 0)
  {
    OCR0B = dutyCycle;
    OCR0A = dutyCycleLow;
    OCR2A = dutyCycleLow;
  }
  else if(counter == 1){
    OCR0B = dutyCycleLow;
    OCR0A = dutyCycle;
    OCR2A = dutyCycleLow;
  }
  else if(counter == 2){
    OCR0B = dutyCycleLow;
    OCR0A = dutyCycleLow;
    OCR2A = dutyCycle;
  }
  else{
    counter = 0;
  }


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
