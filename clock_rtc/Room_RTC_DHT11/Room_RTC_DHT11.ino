// include the library code:
#include <LiquidCrystal.h>
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>


#define DHTPIN 2     // Digital pin connected to the DHT sensor 
#define DHTTYPE    DHT11     // DHT 11

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const char *monthName[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

void setup() {
  // DHT11 init
  Serial.begin(9600);
  while (!Serial) ; // wait until Arduino Serial Monitor opens
  dht.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
  
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
  Serial.println(delayMS);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("Charlotte <3");
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if(timeStatus()!= timeSet) 
     Serial.println("Unable to sync with the RTC");
  else
     Serial.println("RTC has set the system time");      
}

void loop() {
  // Delay between measurements.
  delay(delayMS);
  // print the number of seconds since reset:
  time_t t = now();
  
  // Get temperature event and print its value.
  if (t) {

    sensors_event_t event;
    // set the cursor to column 0, line 0
    lcd.setCursor(1, 0);
    printweekday(weekday(t));
    lcd.print(day(t));
    lcd.print(' ');
    lcd.print(monthName[month(t)-1]);
    lcd.print(' ');
    lcd.print(year(t)-2000);

    //line 1
    // set the cursor to column 0, line 1
    lcd.setCursor(1, 1);
    //print2digits(hourFormat12(t));
    lcd.print(hourFormat12(t));
    lcd.print(':');
    print2digits(minute(t));
    //lcd.print(':');
    //print2digits(second(t));
    if (isPM(t)){
      lcd.print("pm|");
      } else {
      lcd.print("am|");  
      }
    dht.temperature().getEvent(&event);
    // print the temperature
    if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
      }
      else {
        //print2digits(event.temperature);
        lcd.print(int(event.temperature));
        lcd.print(F("C|"));
      }

    // print the humidity
    dht.humidity().getEvent(&event);
    if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
      }
      else {
        print2digits(event.relative_humidity);
        lcd.print('%');
      }
    
    } 
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
     lcd.print("Mon, ");
     break;
     case 2:
     lcd.print("Tue, ");
     break;
     case 3:
     lcd.print("Wed, ");
     break;
     case 4:
     lcd.print("Thu, ");
     break;
     case 5:
     lcd.print("Fri, ");
     break;
     case 6:
     lcd.print("Sat, ");
     break;
     case 0:
     lcd.print("Sun, ");
     break;
}
}
