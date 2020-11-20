#include "Adafruit_NeoPixel.h"
#ifdef __AVR__
    #include <avr/power.h>
#endif

#define PIN            5
#define NUM_LEDS      24
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

//Sinu LED
int led1 = 5;
int LEDval = 0;
//Nupu seaded
int btn = 2;
int buttonNew;
int buttonOld = 1;
int btnState = 0;
long buttonTimer = 0;
long longPressTime = 250;
int emptyR, emptyG, emptyB;
int fullR, fullG, fullB;
int reminderR, reminderG, reminderB;

boolean buttonActive = false;
boolean longPressActive = false;



void ColorMe(int R,int G,int B) {
     for(int i=0;i<NUM_LEDS;i++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    strip.setPixelColor(i, strip.Color(R,G,B)); // Moderately bright green color.
  strip.show(); // This sends the updated pixel color to the hardware
}
}


void theaterChase(uint32_t c, uint8_t wait, int times) {
    for (int j = 0; j < times; j++) { //do 10 cycles of chasing
        for (int q = 0; q < 3; q++) {
            for (int i = 0; i < strip.numPixels(); i = i + 3) {
                strip.setPixelColor(i + q, c);  //turn every third pixel on
            }
            strip.show();

            delay(wait);

            for (int i = 0; i < strip.numPixels(); i = i + 3) {
                strip.setPixelColor(i + q, 0);      //turn every third pixel off
            }
        }
    }
}

void colorWipe(uint32_t c, uint8_t wait) {
    for (uint16_t i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, c);
        strip.show();
        delay(wait);
    }
}
void weightColor(int objectVal){
    if (objectVal > 10.00 && objectVal < 499) {
         digitalWrite(led1, HIGH);
         ColorMe(emptyR,emptyG,emptyB); }
    else if (objectVal > 500 && objectVal < 999) {
      digitalWrite(led1, HIGH);
       ColorMe(fullR,fullG,fullB); 
    }
     else if (objectVal > 1000 && objectVal < 1500) {
      digitalWrite(led1, HIGH);
       ColorMe(reminderR,reminderG,reminderB); 
    }
    else {
       digitalWrite(led1, LOW);
       ColorMe(0,0,0); }
}

void setEmptyCup(String loc){
  String val = "";

  if (Firebase.getString(firebaseData, "/users/" + loc)) {
      if (firebaseData.dataType() == "string") {
          val = firebaseData.stringData();
          long number = strtoll( &val[1], NULL, 16);
          long r = number >> 16;
          long g = number >> 8 & 0xFF;
          long b = number & 0xFF;
          if (loc == "Sarah/hexempty") {
            emptyR = r;
            emptyG = g;
            emptyB = b;
          }
          if (loc == "Sarah/hexfull"){
            fullR = r;
            fullG = g;
            fullB = b;
          }
          if (loc == "Sarah/hexreminder"){
            reminderR = r;
            reminderG = g;
            reminderB = b;
          }
          else {
            Serial.println("Error");
          }
      }
  }
  }
void giveMeInformation(){
      Serial.println("Empty");
      Serial.println(emptyR);
      Serial.println(emptyG);
      Serial.println(emptyB);
      Serial.println("Full");
      Serial.println(fullR);
      Serial.println(fullG);
      Serial.println(fullB);
      Serial.println("Reminder");
      Serial.println(reminderR);
      Serial.println(reminderG);
      Serial.println(reminderB);
      delay(5000);
      }
  
  
  
