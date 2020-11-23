#include "Adafruit_NeoPixel.h"
#ifdef __AVR__
#include <avr/power.h>
#endif
#include <math.h>

// defines LED ring PIN placement on Grove Connector.
#define PIN            5
#define NUM_LEDS      24 // Total LED's on ring.
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);


int btn = 2;
int emptyR, emptyG, emptyB;
int fullR, fullG, fullB;
int reminderR, reminderG, reminderB;

unsigned long holdValue;
unsigned long drinkMinutes;
unsigned long last10Minutes;
unsigned long maxWaitTime = 60000;
unsigned long averageDrinkTime = 30000;


void ColorMe(int R, int G, int B) {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, strip.Color(R, G, B)); 
    strip.show(); 
  }
}

//This function calculates the amount of RGB's that should be ON. A kind of countdown to empty cup.
int oldMultiplied; // Keeps track of old RGB ON amount.
void colorSetter(float currentWeight, float maxReading) {
  float multiplier = ((currentWeight / maxReading)); //
  int multiplied = ((NUM_LEDS * multiplier) + 0.5);
  if ((multiplied) > oldMultiplied) {
    oldMultiplied = multiplied;
    for (int i = 0; i < multiplied; i++) {
      oldMultiplied = multiplied;
      strip.setPixelColor(i, strip.Color(fullR, fullG, fullB)); 
      strip.show();
    } } if (multiplied < oldMultiplied) {
    oldMultiplied = multiplied;
    ColorMe(0, 0, 0);
    for (int i = 0; i < multiplied; i++) {
      oldMultiplied = multiplied;
      strip.setPixelColor(i, strip.Color(fullR, fullG, fullB)); 
      strip.show(); 
    }
  }
}


//Light scene for BOOT.
void theaterChase(uint32_t c, uint8_t wait, int times) {
  for (int j = 0; j < times; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < strip.numPixels(); i = i + 2) {
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

//Store RGB values as HEX values in Database. 
void setupColors(String loc) {
  String empty = "user/hexempty";
  String full = "user/hexfull";
  String reminder = "user/hexreminder";
  String val = "";
  if (Firebase.getString(firebaseData, "/users/" + loc)) {
    if (firebaseData.dataType() == "string") {
      val = firebaseData.stringData();
      // Turns HEX to RGB and places them in the correct values which are used to lights.
      long number = strtoll( &val[1], NULL, 16);
      long r = number >> 16;
      long g = number >> 8 & 0xFF;
      long b = number & 0xFF;
      if (loc == "user/hexempty") {
        emptyR = r;
        emptyG = g;
        emptyB = b;
      }
      if (loc == "user/hexfull") {
        fullR = r;
        fullG = g;
        fullB = b;
      }
      if (loc == "user/hexreminder") {
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
// Provides serial Data to ensure data is being pulled correctly from Database.
void giveMeInformation() {
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

void setColors() {
  String empty = "user/hexempty";
  String full = "user/hexfull";
  String reminder = "user/hexreminder";
  setupColors(empty);
  setupColors(full);
  setupColors(reminder);
  giveMeInformation();
}

int setDrinkReminder() {
  int userReminder =  fetchInt("users/user/remindertime");
  return (((userReminder * 60) * 1000));
}

void blinkReminder(int currentWeight, int currentWeightOld) {
  //Function will not work if current weight is 0, hence backup function below.
  while (constrain(currentWeight, (currentWeightOld * 0.90), (currentWeightOld * 1.10))) {
    currentWeightOld = dataR();
    ColorMe(reminderR, reminderG, reminderB);
    delay(500);
    ColorMe(0, 0, 0);
    delay(500);
  }
}

void blinkEmptyReminder(int currentWeight, int currentWeightOld) {
  while (currentWeight < ((currentWeightOld + 10) * 0.10)) {
    currentWeight = dataR();
    Serial.println(currentWeightOld);
    ColorMe(reminderR, reminderG, reminderB);
    delay(500);
    ColorMe(0, 0, 0);
    delay(500);
  }
}

// Automattically counts the amounts of drinks within a degree of accuracy 
// (currentWeight < 11) is used due to a rounding function, in dataR();. Rounds to nearest 10.
void drinkCounter(int currentWeight, int maxReading, String currentDate) {
  if (currentWeight < 11) {
    holdValue = millis();
    while (currentWeight < 11 && maxReading != 0) {
      currentWeight = dataR();
      //User has 30 seconds to drink and replace glass on coaster, before additional timer starts.
      while (currentWeight < 11 && (millis() - holdValue) >= averageDrinkTime) {
        // Redundent check, however without a break; inside this function. Function runs incorrectly.
        while (maxReading != 0) {
          currentWeight = dataR();
          while (currentWeight < 11) {
            drinkMinutes = millis();
            while ((millis() - drinkMinutes) <= maxWaitTime) {
              currentWeight = dataR();
              // The loop assumes that the user is refilling glass after the 30 second period.
              // if user replaces glass on scale 
              if (currentWeight > (maxReading * 0.60) && (millis() - drinkMinutes) <= (maxWaitTime - 1000)) {
                int currentDrinkTotal= fetchInt("users/user/drinktotal/" + currentDate); //Gets current number sorted in Database when called.
                Firebase.setInt(firebaseData, "users/user/drinktotal/" + currentDate, (currentDrinkTotal + 1)); // Number stored in N + 1 uploaded to server.
                break;
              }
              if (currentWeight < (maxReading * 0.60) && (millis() - drinkMinutes) >= (maxWaitTime - 1000)) {
                blinkEmptyReminder(currentWeight, currentWeight);
                break;
              }
            }
          }
          break;
        }
      }
    }
  }
}
