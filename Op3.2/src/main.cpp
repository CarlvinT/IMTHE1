#include <avr/io.h>
#include <util/delay.h>
#include <arduino.h>


void initADC(){
    ADMUX |= (1 << REFS0); // Zet op 5V
    ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); // Zet divider op 128 voor 10 bit precisie
    ADCSRA |= (1 << ADEN); // AD Enable
}

uint16_t readADC(){
    ADCSRA |= (1 << ADSC); //start reading
    loop_until_bit_is_clear(ADCSRA, ADSC); //wait until done
    return ADC; //Geef de ADC waarde
}

void opstelling(){
  Serial.begin(9600);
  initADC();
}

// Main function so program can run
int main(void){
    // Run code that only needs to be run once (setup)
    opstelling();

    // Same as Loop() in adruino. Infite loop while 1.
    while(1){
      Serial.println(readADC());


    }// Return 0 cause main is int
    return 0;
}
