/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

// include the library code:
#include <LiquidCrystal.h>
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const char *monthName[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("Charlotte <3");
  Serial.begin(9600);
  while (!Serial) ; // wait until Arduino Serial Monitor opens
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if(timeStatus()!= timeSet) 
     Serial.println("Unable to sync with the RTC");
  else
     Serial.println("RTC has set the system time");      
}

void loop() {
  // print the number of seconds since reset:
  time_t t = now();
  if (t) {
    // set the cursor to column 0, line 0
    lcd.setCursor(0, 0);
    printweekday(weekday(t));
    lcd.print(" ");
    lcd.print(day(t));
    lcd.print('.');
    lcd.print(monthName[month(t)-1]);
    lcd.print('.');
    lcd.print(year(t)-2000);

    //line 1
    // set the cursor to column 0, line 1
    lcd.setCursor(0, 1);
    //lcd.print("");
    //print2digits(hourFormat12(t));
    lcd.print(hourFormat12(t));
    lcd.print(':');
    print2digits(minute(t));
    //lcd.print(':');
    //print2digits(second(t));
    if (isPM(t)){
      lcd.print("pm");
      } else {
      lcd.print("am");  
      } 
    } 
  delay(1000);
}

void print2digits(int number) {
  if (number >= 0 && number < 10) {
    lcd.print('0');
  }
  lcd.print(number);
}

void printweekday(int number){
switch(number-1){
     case 1:
     lcd.print("Mon");
     break;
     case 2:
     lcd.print("Tue");
     break;
     case 3:
     lcd.print("Wed");
     break;
     case 4:
     lcd.print("Thu");
     break;
     case 5:
     lcd.print("Fri");
     break;
     case 6:
     lcd.print("Sat");
     break;
     case 0:
     lcd.print("Sun");
     break;
}
}
