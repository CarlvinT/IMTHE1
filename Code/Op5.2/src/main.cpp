#include <avr/io.h>
#include <util/delay.h>
#include "Adafruit_LiquidCrystal.h"
#include <utility\Adafruit_MCP23008.h>

/*The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)*/


Adafruit_LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void opstelling(){
  // set up the LCD's number of rows and columns:
  lcd.begin(16, 2);

// set cursor and text
  lcd.setCursor(0,0);
  lcd.print("Carlvin Tromp");
// set cursor and text 
  lcd.setCursor(0,1);
  lcd.print("S1089951");
}



// Main function so program can run
int main(void){

    // Run code that only needs to be run once (setup)
    opstelling();

    // Same as Loop() in adruino. Infite loop while 1.
    while(1){

    }// Return 0 cause main is int
    return 0;
}
