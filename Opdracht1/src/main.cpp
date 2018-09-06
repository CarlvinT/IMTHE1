
#include <avr/io.h>
#include <util/delay.h>


// Main function so program can run
int main(void){

    // Define Pin and data bank
    DDRB = 0b000100000; //DDR + Data bank letter = 0b000100000 set pin number to 1 that is gonna be active

    // Same as Loop() in adruino. Infite loop while 1.
    while(1){
        //
        PORTB = 0b000100000; // Set pin pb5 to high with data bank B
        _delay_ms(2000); //Wacht 2 seconden
        PORTB = 0b000000000; //Set pin to LOW with data bank B
        _delay_ms(2000);
    }

    // Return 0 cause maint is int
    return 0;

}
