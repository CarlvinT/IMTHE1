
#include <avr/io.h>
#include <util/delay.h>

void opstelling(){
  // Define Pin and data bank
  DDRD = 0b00100000;
}

void blinks(){
  PORTD = 0b00100000;
  _delay_ms(1000); // Delay by 1 second
  PORTD = 0b00000000;
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
