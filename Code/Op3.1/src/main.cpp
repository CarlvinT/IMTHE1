#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
/*

BUtton = PB3

Lights:
PC0 PC3 PD4
PC1 PC4 PD3
PC2 PC5 PD2


*/
bool swiching = false;


void opstelling(){
  DDRC = 0xff;
  DDRD = 0xff;
  PORTC = 0x00;
  PORTD = 0x00;

  PORTB |= (1<<3);
}

void reset(){
  PORTC = 0x00;
  PORTD = 0x00;
}

void setNumber(int number){
  reset();
  if(number == 1)
  {
    PORTC |= (1<< PC4);
  }
  else if(number == 2)
  {
      PORTD |= (1<< PD4);
      PORTC |= (1<< PC2);
  }
  else if(number == 3)
  {
      PORTD |= (1<< PD4);
      PORTC |= (1<< PC2);
      PORTC |= (1<< PC4);
  }
  else if(number == 4)
  {
    PORTD |= (1<< PD4);
    PORTC |= (1<< PC2);
    PORTC |= (1<< PC0);
    PORTD |= (1<< PD2);
  }
  else if(number == 5)
  {
    PORTD |= (1<< PD4);
    PORTC |= (1<< PC2);
    PORTC |= (1<< PC0);
    PORTC |= (1<< PC4);
    PORTD |= (1<< PD2);
  }
  else if(number == 6)
  {
    PORTC = 0xff;
    PORTD = 0xff;
  }

}

// Main function so program can run
int main(void){
    // Run code that only needs to be run once (setup)
    opstelling();

    // Same as Loop() in adruino. Infite loop while 1.
    while(1){
      if (bit_is_clear(PINB, PB3)){
        // PRESSED
        if (swiching == false){
          setNumber(rand() % 6 + 1);
          _delay_ms(200);
        }
        swiching = true;
      }
      else {
        // NOT PRESSED
        if (swiching == true)
        {
          swiching = false;
        }
      }






    }// Return 0 cause main is int
    return 0;
}
