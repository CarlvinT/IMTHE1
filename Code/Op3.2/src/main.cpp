#include <avr/io.h>
#include <util/delay.h>

//Reading ADC values explanation begins at page 137
/*
POTMETER = G A0 5v
Speaker = D2 G
*/

static inline void initADC(void){
    ADMUX |= (1 << REFS0); // Zet reference voltage naar interal AREF 5V
    ADCSRA |= (1 << ADPS0) | (1 << ADPS1); // Prescale op 8 want het heeft een max van 125khz dat is dus binnen de 100 t/m 10khz requirments
    ADCSRA |= (1 << ADEN); // AD Enable
    //Pin is automatisch gezet op PC0
}

uint16_t getADC(){
    ADCSRA |= (1 << ADSC); //Start conversion bij ADC Status register A</arduino.h>
    loop_until_bit_is_clear(ADCSRA, ADSC); // wacht tot dat het klaar is
    ADCSRA &= ~(1 << ADSC); // turn of conversion
    return ADC; //Return ADC Waarde
  }

// Je moet je eigen delay function maken want _delay_ms vind variables niet zo leuk.
void delay_ms( int ms )
{
   for (int i = 0; i < ms; i++)
   {
      _delay_ms(1);
   }
}

void opstelling(){
  DDRD |= (1<<2);
  initADC();  // Begin analog to digital conversion
}

int getFrequency(){
  /*
  100hz = 100 time per second.
  10ms = 0.01 seconds.  100 times * 0.01 = 1s
  Dus met een basis delay van 10ms het speaker zou een frequency van 100hz hebben

  10,000hz = 100hz * 100.
  Potentiometer values = 0 to 1028
  Potmeter value / 10 = 0 to 102
  bij max van 102 * 100hz = 10,200hz dus 10,000hz

  uiteindelijk /2 om de delay eerlijk te splitsen tussen on and off
  */
  uint16_t baseDelay = 10;
  uint16_t base = baseDelay * (getADC()/10 + 1) ;
  uint16_t Frequency = base/2;
  return Frequency;
}



// Main function so program can run
int main(void){
    // Run code that only needs to be run once (setup)
    opstelling();

    // Same as Loop() in adruino. Infite loop while 1.
    while(1){
      uint16_t msDelay = getFrequency();

      PORTD ^= (1<<PD2);
      delay_ms(msDelay);
      PORTD ^= (1<<PD2);
      delay_ms(msDelay);


    }// Return 0 cause main is int
    return 0;
}
