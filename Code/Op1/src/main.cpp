
#include <avr/io.h>
#include <util/delay.h>

void opstelling(){
  // Define Pin and data bank
  DDRD = 0xff; // set register as ouput
  PORTD |= (1<<2);  // set pin as high
  PORTD &= ~(1<<3); // set pin as low
}

void blinks(){
  // flip the pin states
PORTD ^= (1<<2);
PORTD ^= (1<<3);
// wait 1 sec
_delay_ms(1000);
}

// Main function so program can run
int main(void){
    // Run code that only needs to be run once (setup)
    opstelling();

    // Same as Loop() in adruino. Infite loop while 1.
    while(1){
      blinks();
    }

    // Return 0 cause main is int
    return 0;
}
