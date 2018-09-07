
#include <avr/io.h>
#include <util/delay.h>

void setup(){
  // Define Pin and data bank
  DDRD = 0b00100000; //DDR + Data bank letter = 0b000100000 set pin number to 1 that is gonna be active
}

void blinks(){
  PORTD = 0b00100000; // Set pin pb5 to high with data bank B
  _delay_ms(1000); //Wacht 2 seconden
  PORTD = 0b00000000; //Set pin to LOW with data bank B
  _delay_ms(1000);
}

// Main function so program can run
int main(void){
    // Run code that only needs to be run once (setup)
    setup();

    // Same as Loop() in adruino. Infite loop while 1.
    while(1){
      blinks();
    }

    // Return 0 cause main is int
    return 0;

}
