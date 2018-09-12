//Imports
#include <avr/io.h> // IO PIN LIBRARY
#include <util/delay.h>// DELAY LIBRARY

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
int delayTime = 1000;

void opstelling(){

  // SET GROUPS AS OUTPUT
  DDRD = 0xff; // SET ALL PINS AS OUTPUT IN D
  DDRB = 0xff; // SET ALL PINS AS OUTPUT IN B

  // SET ALL PINS AS HIGH
  //PORTD = 0xff; // SET ALL PINS AS HIGH IN D
  //PORTB = 0xff; // SET ALL PINS AS HIHGH IN B
}

void setNumberRight(int number){
  // 8,9 B Bank
  if ( number == 0 ) {
    DDRB = 0b00000011;
    DDRD = 0b10101100;
  }
  else if ( number == 1 ) {
    DDRB = 0b00000000;
    DDRD = 0b10100000;
  }
  else if ( number == 2 ) {
    DDRB = 0b00000001;
    DDRD = 0b10011100;
  }
  else if ( number == 3 ) {
    DDRB = 0b00000001;
    DDRD = 0b10111000;
  }
  else if ( number == 4 ) {
    DDRB = 0b00000010;
    DDRD = 0b10110000;
  }
  else if ( number == 5 ) {
    DDRB = 0b00000011;
    DDRD = 0b00111000;
  }
  else if ( number == 6 ) {
    DDRB = 0b00000011;
    DDRD = 0b00111100;
  }
  else if ( number == 7 ) {
    DDRB = 0b00000001;
    DDRD = 0b10100000;
  }
  else if ( number == 8 ) {
    DDRB = 0b00000011;
    DDRD = 0b10111111;
  }
  else if ( number == 9 ) {
    DDRB = 0b00000011;
    DDRD = 0b10111000;
  }

}

void setNumberLeft(int number){
  // 8,9 B Bank
  if ( number == 0 ) {
    DDRB = 0b00000011;
    DDRD = 0b10101100;
  }
  else if ( number == 1 ) {
    DDRB = 0b00000000;
    DDRD = 0b10100000;
  }
  else if ( number == 2 ) {
    DDRB = 0b00000001;
    DDRD = 0b10011100;
  }
  else if ( number == 3 ) {
    DDRB = 0b00000001;
    DDRD = 0b10111000;
  }
  else if ( number == 4 ) {
    DDRB = 0b00000010;
    DDRD = 0b10110000;
  }
  else if ( number == 5 ) {
    DDRB = 0b00000011;
    DDRD = 0b00111000;
  }
  else if ( number == 6 ) {
    DDRB = 0b00000011;
    DDRD = 0b00111100;
  }
  else if ( number == 7 ) {
    DDRB = 0b00000001;
    DDRD = 0b10100000;
  }
  else if ( number == 8 ) {
    DDRB = 0b00000011;
    DDRD = 0b10111111;
  }
  else if ( number == 9 ) {
    DDRB = 0b00000011;
    DDRD = 0b10111000;
  }

}

void setNumbers(int row, int number){
  if ( row == 1) {
    setNumberLeft(number);
  }
  else if( row == 2 ) {
    setNumberRight(number);
  }

}

void countToTen(){
  for( int a = 0; a < 10; a = a + 1 ) {
   setNumberRight(a);
   _delay_ms(delayTime);
  }
  /*setNumberRight(0);
  _delay_ms(delayTime);
  setNumberRight(1);
  _delay_ms(delayTime);
  setNumberRight(2);
  _delay_ms(delayTime);
  setNumberRight(3);
  _delay_ms(delayTime);
  setNumberRight(4);
  _delay_ms(delayTime);
  setNumberRight(5);
  _delay_ms(delayTime);
  setNumberRight(6);
  _delay_ms(delayTime);
  setNumberRight(7);
  _delay_ms(delayTime);
  setNumberRight(8);
  _delay_ms(delayTime);
  setNumberRight(9);
  _delay_ms(delayTime);*/
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
