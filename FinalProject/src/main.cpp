#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/*
  SOURCES:
  https://www.mouser.com/ds/2/813/HCSR04-1022824.pdf
  https://www.mpja.com/download/hc-sr04_ultrasonic_module_user_guidejohn.pdf
  https://www.mpja.com/download/hc-sr04_ultrasonic_module_user_guidejohn.pdf
  http://ww1.microchip.com/downloads/en/devicedoc/atmel-42735-8-bit-avr-microcontroller-atmega328-328p_datasheet.pdf
*/

uint16_t counter = 0; // Timer distance counter, used in checkDistance()
uint32_t counter2 = 0; // Used to check elapsed time to trigger code

// timer setup
void initTimer(void) {

  //(DISTANCE) Timer 1 setting up counter for distance measurements
  TCCR1B |= (1 << CS11); // set clockspeed prescaler to 8 (1 clock tick = 8 us)
  TIMSK1 |= (0 << TOIE1); // Disable timer intterupt


  //(TIMER) Setup timer 0 will trigger every 1 second to check distance
  TCCR0B |= (1 << CS12) | (1 << CS10); // set clockspeed prescaler to 1024 (1 clock tick = 1.024 ms)
  TIMSK0 |= (1 << TOIE0); // Enable timer intterupt


  //(PWM) Timer 2 Setting up pwm for speaker
  TCCR2A|= (1 << WGM20) | (1 << WGM21) | (1 << COM2B1) ;//WGM20 | WGM21 = turning on 2 bits in the register to setup pwm mode / COM2A1 = setting up pin to switch when comparator reached
  TCCR2B |= (1 << CS12) | (1 << CS10); /* PWM Freq = F_CPU/8/256(Setting up frequency) */

  OCR2B = 255; // setup comparator frequency



  //TIMER0_OVF_vect |  TIMER0_COMPB_vect instead of overflow, when timer reaches comparator
}

// get distance
int getDistance(){
  uint32_t microseconds;
  uint16_t distance;

  TIMSK1 |= (1 << TOIE0); // Enable timer intterupt

  // Send pin out to high for 10us to start the measurement process.
  PORTB |= (1<<4);
  _delay_us (10);
  PORTB &= ~(1<<4);

  // reset counters
  TCNT1 = 0;
  counter = 0;

  // do nothing while message is coming in
  loop_until_bit_is_set(PINB, PB3);
  loop_until_bit_is_clear(PINB, PB3);

  // calculate distance
  microseconds = TCNT1 * 8; // add current microseconds
  TCNT1 = 0; // reset timer
  microseconds += (counter * 65535) * 8; // calculate total microseconds in counter
  counter = 0; // reset counter

  // calculate distance based on website specifics
  distance = (microseconds/2) / 58;

  // return distance in CM
  return distance;
  TIMSK1 |= (0 << TOIE0); // Disable timer intterupt
  _delay_ms(1000);


}


//(DISTANCE) everytime it over +1 to check time in microseconds for distance checking
ISR(TIMER1_OVF_vect){
counter += 1;

}

//(TIMER) check distance and switch speaker frequency when it overflows
ISR(TIMER0_OVF_vect){

//counter2 += 1;
TIMSK0 |= (0 << TOIE0); // Enable timer intterupt

/* Set total type elapsed in microseconds (*8 because prescaler = 8 microseconds per clock tik)
uint32_t microseconds = (counter2 * 255) * 8; // get time in microseconds stored in counter2
microseconds += TCNT0 * 8; // add value stored in counter register*/

// check time elapsed and set speaker frequency


  uint8_t distance = getDistance();

  if(distance >= 200){
      DDRD &= ~(1<<3);
  }
  else if(distance >= 110){
      DDRD |= (1<<3);
      OCR2B = 100;

  }
  else if (distance >= 90){
      DDRD |= (1<<3);
      OCR2B = 235;
  }
  else{
      DDRD |= (1<<3);
      OCR2B = 245;
  }

  counter2 = 0; // reset counter2
  TIMSK0 |= (1 << TOIE0); // Enable timer intterupt
}


void opstelling(){
  DDRB |= (1<<4);
  DDRD |= (1<<3);
  PORTB &= ~(1<<4); // trigger pin
  initTimer();
  sei(); // start intterupts.
}


int main(void){

    // Run code that only needs to be run once (setup)
    opstelling();

    // Same as Loop() in adruino. Infite loop while 1.
    while(1){
    }// Return 0 cause main is int
    return 0;
}
