
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>


/* Wiring info

Wiring :
current wiring  =
- - - - + + 9 8 7
- - - - 2 3 4 5 6


// Right side
Led number sequence right side:
1 = 5,7
2 = 8,7,4,2,3
3 = 8,7,5,3,4
4 = 9,7,4,5
5 = 8,9,4,5,3
6 = 8,5,4,2,5,3
7 = 8,7,5
8 = 8,9,7,4,2,5,3
9 = 8,9,7,4,5,3
0 = 8,9,7,2,5,3

Pin to led binding:
E = 2
D = 3
C = 5
DP = 6
G = 4
F = 9
B = 7
A = 8


*/

uint8_t  LNumber = 0;

void clearNumbers(){
  PORTD = 0xff;
  PORTB = 0xff;
  PORTC = 0xff;
}

void clearRight(){
  PORTD = 0xFF;
  PORTB |= (1<<1);
  PORTB |= (1<<2);
}



void opstelling(){
  // Define Pin and data bank
  DDRD = 0xff;
  DDRB = 0xff;
  DDRC = 0xff;
  clearNumbers();
}

void setNumberRight(uint8_t  number){
  // 8,9 B Bank
  if ( number == 0 ) {
    clearNumbers();
    PORTB &= ~(1<<0);
    PORTB &= ~(1<<1);
    PORTD &= ~(1<<7);
    PORTD &= ~(1<<2);
    PORTD &= ~(1<<5);
    PORTD &= ~(1<<3);

  }
  else if ( number == 1 ) {
    clearNumbers();
    PORTD &= ~(1<<5);
    PORTD &= ~(1<<7);
  }
  else if ( number == 2 ) {
    clearNumbers();
    PORTB &= ~(1<<0);
    PORTD &= ~(1<<7);
    PORTD &= ~(1<<4);
    PORTD &= ~(1<<2);
    PORTD &= ~(1<<3);
  }
  else if ( number == 3 ) {
    clearNumbers();
    PORTB &= ~(1<<0);
    PORTD &= ~(1<<7);
    PORTD &= ~(1<<5);
    PORTD &= ~(1<<3);
    PORTD &= ~(1<<4);
  }
  else if ( number == 4 ) {
    clearNumbers();
    PORTB &= ~(1<<1);
    PORTD &= ~(1<<7);
    PORTD &= ~(1<<4);
    PORTD &= ~(1<<5);

  }
  else if ( number == 5 ) {
    clearNumbers();
    PORTB &= ~(1<<0);
    PORTB &= ~(1<<1);
    PORTD &= ~(1<<4);
    PORTD &= ~(1<<5);
    PORTD &= ~(1<<3);
  }
  else if ( number == 6 ) {
    clearNumbers();
    PORTB &= ~(1<<0);
    PORTB &= ~(1<<1);
    PORTD &= ~(1<<5);
    PORTD &= ~(1<<4);
    PORTD &= ~(1<<2);
    PORTD &= ~(1<<3);
  }
  else if ( number == 7 ) {
    clearNumbers();
    PORTB &= ~(1<<0);
    PORTD &= ~(1<<7);
    PORTD &= ~(1<<5);
  }
  else if ( number == 8 ) {
    clearNumbers();
    PORTB &= ~(1<<0);
    PORTB &= ~(1<<1);
    PORTD &= ~(1<<7);
    PORTD &= ~(1<<4);
    PORTD &= ~(1<<2);
    PORTD &= ~(1<<5);
    PORTD &= ~(1<<3);

  }
  else if ( number == 9 ) {
    clearNumbers();
    PORTB &= ~(1<<0);
    PORTB &= ~(1<<1);
    PORTD &= ~(1<<7);
    PORTD &= ~(1<<4);
    PORTD &= ~(1<<5);
    PORTD &= ~(1<<3);
  }

}



void countToTen(){
  for( int a = 0; a < 10; a = a + 1 ) {
   setNumberRight(a);
   _delay_ms(1000);
  }
}

// Main function so program can run
int main(void){
    // Run code that only needs to be run once (setup)
    opstelling();

    // Same as Loop() in adruino. Infite loop while 1.
    while(1){
      countToTen();
    }

    // Return 0 cause main is int
    return 0;
}
