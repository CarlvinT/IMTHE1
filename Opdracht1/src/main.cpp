/*
 * main.c
 *
 *  Created on: 5 sep. 2018
 *      Author: jande_000
 */

#include <avr/io.h>
#include <util/delay.h>

int main(void){

    DDRB = 0b000100000; //Define Pin and data bank

    while(1){
        //programma

        PORTB = 0b000100000; // Set pin pb5 to high with data bank B
        _delay_ms(2000); //Wacht 2 seconden
        PORTB = 0b000000000; //Set pin to LOW with data bank B
        _delay_ms(2000);
    }
    return 0;

}
