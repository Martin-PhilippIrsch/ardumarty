#include "LedControl.h"


/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to LOAD(CS)
 pin 10 is connected to the CLK 
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(12,10,11,1);

byte six[8]={B00000000,B11011011,B11011011,B00000000,B00000000,B11011011,B11011011,B00000000};
byte five[8]={B00000000,B01100110,B01100110,B00011000,B00011000,B01100110,B01100110,B00000000};
byte four[8]={B00000000,B01100110,B01100110,B00000000,B00000000,B01100110,B01100110,B00000000};
byte three[8]={B11000000,B11000000,B00000000,B00011000,B00011000,B00000000,B00000011,B00000011};
byte two[8]={B00000000,B00000000,B00000000,B01100110,B01100110,B00000000,B00000000,B00000000};
byte one[8]={B00000000,B00000000,B00000000,B00011000,B00011000,B00000000,B00000000,B00000000};
byte refresh[8]={B11111111,B10000001,B10111101,B10100101,B10100101,B10111101,B10000001,B11111111};
byte dark[8]={B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000};



unsigned long delaytime1=1000;
unsigned long delaytime2=200;


void make_one(){
  lc.setRow(0,0,one[0]);
  lc.setRow(0,1,one[1]);
  lc.setRow(0,2,one[2]);
  lc.setRow(0,3,one[3]);
  lc.setRow(0,4,one[4]);
  lc.setRow(0,5,one[5]);
  lc.setRow(0,6,one[6]);
  lc.setRow(0,7,one[7]);
}

void make_two(){
  lc.setRow(0,0,two[0]);
  lc.setRow(0,1,two[1]);
  lc.setRow(0,2,two[2]);
  lc.setRow(0,3,two[3]);
  lc.setRow(0,4,two[4]);
  lc.setRow(0,5,two[5]);
  lc.setRow(0,6,two[6]);
  lc.setRow(0,7,two[7]);
}

void make_three(){
  lc.setRow(0,0,three[0]);
  lc.setRow(0,1,three[1]);
  lc.setRow(0,2,three[2]);
  lc.setRow(0,3,three[3]);
  lc.setRow(0,4,three[4]);
  lc.setRow(0,5,three[5]);
  lc.setRow(0,6,three[6]);
  lc.setRow(0,7,three[7]);
}

void make_four(){
  lc.setRow(0,0,four[0]);
  lc.setRow(0,1,four[1]);
  lc.setRow(0,2,four[2]);
  lc.setRow(0,3,four[3]);
  lc.setRow(0,4,four[4]);
  lc.setRow(0,5,four[5]);
  lc.setRow(0,6,four[6]);
  lc.setRow(0,7,four[7]);
}

void make_five(){
  lc.setRow(0,0,five[0]);
  lc.setRow(0,1,five[1]);
  lc.setRow(0,2,five[2]);
  lc.setRow(0,3,five[3]);
  lc.setRow(0,4,five[4]);
  lc.setRow(0,5,five[5]);
  lc.setRow(0,6,five[6]);
  lc.setRow(0,7,five[7]);
}

void make_six(){
  lc.setRow(0,0,six[0]);
  lc.setRow(0,1,six[1]);
  lc.setRow(0,2,six[2]);
  lc.setRow(0,3,six[3]);
  lc.setRow(0,4,six[4]);
  lc.setRow(0,5,six[5]);
  lc.setRow(0,6,six[6]);
  lc.setRow(0,7,six[7]);
}

void make_refresh(){
  lc.setRow(0,0,refresh[0]);
  lc.setRow(0,1,refresh[1]);
  lc.setRow(0,2,refresh[2]);
  lc.setRow(0,3,refresh[3]);
  lc.setRow(0,4,refresh[4]);
  lc.setRow(0,5,refresh[5]);
  lc.setRow(0,6,refresh[6]);
  lc.setRow(0,7,refresh[7]);
}

void make_dark(){
  lc.setRow(0,0,dark[0]);
  lc.setRow(0,1,dark[1]);
  lc.setRow(0,2,dark[2]);
  lc.setRow(0,3,dark[3]);
  lc.setRow(0,4,dark[4]);
  lc.setRow(0,5,dark[5]);
  lc.setRow(0,6,dark[6]);
  lc.setRow(0,7,dark[7]);
}

int buttonStartpin = 7;
int buttonEndpin = 6;

void setup()
{
  pinMode(buttonStartpin, INPUT_PULLUP);
  pinMode(buttonEndpin, INPUT_PULLUP);
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,2);
  /* and clear the display */
  lc.clearDisplay(0);

  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));
  make_refresh();
  delay(delaytime2);
  make_dark();

}

void loop()
{

  if (digitalRead(buttonEndpin) == LOW)
    {
      make_dark();
    }

  if (digitalRead(buttonStartpin) == LOW)
    {
     randomSeed(analogRead(0));
     int x = random(1,7);
     make_dark();
     delay(delaytime2);
     make_refresh();
     delay(delaytime2);
     make_dark();
     delay(delaytime2);
     make_refresh();
     delay(delaytime2);
     make_dark();
     delay(delaytime2);
     make_refresh();
     delay(delaytime1);
     
     switch(x){
        case 1 : make_one();
        break;
        case 2 : make_two();
        break;
        case 3 : make_three();
        break;
        case 4 : make_four();
        break;
        case 5 : make_five();
        break;
        case 6 : make_six();
        break;
      }

    }
  
  
  
}
