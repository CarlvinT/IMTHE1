
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

// left side
Led number sequence right side:
1 =
2 =
3 =
4 =
5 =
6 =
7 =
8 =
9 =
0 =

Pin to led binding:
E =
D =
C =
DP =
G =
F =
B =
A =

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

void clearLeft(){
  PORTC = 0xff;
  PORTB |= (1<<7);
  PORTB |= (1<<6);
  PORTB |= (1<<5);
  PORTB |= (1<<4);
  PORTB |= (1<<3);
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

void setNumberLeft(uint8_t  number){
  /*
        A = PC1

F = PC3         B = PC0

        G = PC2

E = PB4         C = PB2

        D = PB3

*/
  if ( number == 0 ) {
    clearLeft();
    PORTC &= ~(1<< PC0);
    PORTC &= ~(1<< PC3);
    PORTC &= ~(1<< PC1);
    PORTB &= ~(1<< PB4);
    PORTB &= ~(1<< PB2);
    PORTB &= ~(1<< PB3);

  }
  else if ( number == 1 ) {
    clearLeft();
    PORTC &= ~(1<< PC0);
    PORTB &= ~(1<< PB2);
  }
  else if ( number == 2 ) {
    clearLeft();
    PORTC &= ~(1<< PC1);
    PORTC &= ~(1<< PC0);
    PORTC &= ~(1<< PC2);
    PORTB &= ~(1<< PB4);
    PORTB &= ~(1<< PB3);
  }
  else if ( number == 3 ) {
    clearLeft();
    PORTC &= ~(1<< PC1);
    PORTC &= ~(1<< PC0);
    PORTC &= ~(1<< PC2);
    PORTB &= ~(1<< PB2);
    PORTB &= ~(1<< PB3);
  }
  else if ( number == 4 ) {
    clearLeft();
    PORTC &= ~(1<< PC3);
    PORTC &= ~(1<< PC0);
    PORTC &= ~(1<< PC2);
    PORTB &= ~(1<< PB2);

  }
  else if ( number == 5 ) {
    clearLeft();
    PORTC &= ~(1<< PC1);
    PORTC &= ~(1<< PC3);
    PORTC &= ~(1<< PC2);
    PORTB &= ~(1<< PB2);
    PORTB &= ~(1<< PB3);
  }
  else if ( number == 6 ) {
    clearLeft();
    PORTC &= ~(1<< PC1);
    PORTC &= ~(1<< PC3);
    PORTC &= ~(1<< PC2);
    PORTB &= ~(1<< PB4);
    PORTB &= ~(1<< PB2);
    PORTB &= ~(1<< PB3);
  }
  else if ( number == 7 ) {
    clearLeft();
    PORTC &= ~(1<< PC1);
    PORTC &= ~(1<< PC0);
    PORTB &= ~(1<< PB2);
  }
  else if ( number == 8 ) {
    clearLeft();
    PORTC &= ~(1<< PC0);
    PORTC &= ~(1<< PC3);
    PORTC &= ~(1<< PC1);
    PORTC &= ~(1<< PC2);
    PORTB &= ~(1<< PB4);
    PORTB &= ~(1<< PB2);
    PORTB &= ~(1<< PB3);
  }
  else if ( number == 9 ) {
    clearLeft();
    PORTC &= ~(1<< PC0);
    PORTC &= ~(1<< PC3);
    PORTC &= ~(1<< PC1);
    PORTC &= ~(1<< PC2);
    PORTB &= ~(1<< PB2);
    PORTB &= ~(1<< PB3);
  }

}


void countToTen(){
  for( uint8_t  a = 0; a < 10; a = a + 1 ) {
   setNumberRight(a);
   _delay_ms(1000);
  }
}

void countToHundred(){
  if (LNumber == 10)
  {
    LNumber = 0;
  }
  for( uint8_t  a = 0; a < 10; a = a + 1 ) {
    setNumberRight(a);
    setNumberLeft(LNumber);
    if (a == 9)
    {
      LNumber += 1;
    }
   _delay_ms(1000);
  }
}

// Main function so program can run
int  main(void){
    // Run code that only needs to be run once (setup)
    opstelling();

    // Same as Loop() in adruino. Infite loop while 1.
    while(1){
      countToHundred();
    }

    // Return 0 cause main is uint8_t
    return 0;
}
