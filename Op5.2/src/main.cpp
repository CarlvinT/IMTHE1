#include <avr/io.h>
#include <util/delay.h>
#include "Adafruit_LiquidCrystal.h"
#include <utility\Adafruit_MCP23008.h>


Adafruit_LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void opstelling(){
  // set up the LCD's number of rows and columns:
  lcd.begin(16, 2);

  lcd.setCursor(0,0);
  lcd.print("Carlvin Tromp");

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
