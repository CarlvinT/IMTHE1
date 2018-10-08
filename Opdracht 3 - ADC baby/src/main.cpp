#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

void opstelling(){
  DDRC = 0xff;
}

/*
X AXIS: ALWAYS ON HIGH
PC3 = led pin 7 (X AXIS row 1)
PC5 = led pin 2 (X AXIS row 2)
PC4 = led pin 5 (X AXIS row 3)


Y AXIS: ALWAYS ON LOW
PC2 = led pin 13(Y AXIS ROW 1)
PC1 = led pin 3 (Y AXIS ROW 2)
PC0 = led pin 4 (y AXIS ROW 3)

DOT COMBINATION:
1=
2=
3=
4=
5=
6=


*/

void blinks(){
  PORTC |= (1<<5);
  PORTC |= (1<<4);
  PORTC |= (1<<3);
  _delay_ms(1000);
  PORTC &= ~(1<<5);
  PORTC &= ~(1<<4);
  PORTC &= ~(1<<3);
  _delay_ms(1000);

}

void clearNumber(){
 PORTC = 0xff;
}


void setNumber(int number)
{
  if(number == 0)
  {
    PORTC &= ~(1<<3);
    PORTC &= ~(1<<4);
    PORTC &= ~(1<<2);
    PORTC &= ~(1<<0);


  }
  else if(number == 1)
  {

  }

}

// Main function so program can run
int main(void){
    // Run code that only needs to be run once (setup)
    opstelling();

    // Same as Loop() in adruino. Infite loop while 1.
    while(1){
      setNumber(0);



    }// Return 0 cause main is int
    return 0;
}
