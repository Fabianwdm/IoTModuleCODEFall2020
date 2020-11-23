#include "dateChecker.h"
#include "secret.h"
#include "Firebase_Arduino_WiFiNINA.h"
#include "firebaseConnection.h"
#include "light.h"
#include "HX711.h"
#include "Adafruit_NeoPixel.h"

#define BUTTON_PIN   0

long TENMINUTES = 0;
float previousValue;
int maxReading = 1000;



void setup() {
  Serial.begin(9600);
  pinMode(PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  strip.setBrightness(100);
  theaterChase(strip.Color(127, 127, 127), 50, 20);
  firebaseSetup();
  String todaysDateFormatted = TodaysDate();
  updateDateServer(todaysDateFormatted);
  setupWeight();

  //maxReading = getMaxWeight();
  scale.tare();
  ColorMe(0, 0, 0);
  setColors();
  delay(2000);
  TENMINUTES = setDrinkReminder();
}

float oldObjectVal;
int buttonNew = digitalRead(BUTTON_PIN);

void loop() {
  /*
    Serial.println(maxReading);
    delay(2000);
    /*
    Serial.println(getUser());
    updateDate();
  */

  /*
    Serial.print("Date: ");
    Serial.println(timeS());
    delay(1000);
  */
  float objectVal = dataR();
  Serial.println(objectVal);

  if (buttonNew == 1) {
    maxReading = maxData();
    delay(500);
    updateMaxWeight(maxReading);
  }

  colorSetter(objectVal, maxReading);
  if (objectVal < (maxReading * 0.98)) {
    float objectVal = dataR();
    drinkCounter(objectVal, maxReading);
  }


  /*
    if (millis() - last10Minutes >= TENMINUTES) {
     last10Minutes += TENMINUTES;
     Serial.println("One Minutes Has Passed");
     if (objectVal < 10) {
       Serial.println("I am here");
       blinkEmptyReminder(objectVal, objectVal);
     } else {
       blinkReminder(objectVal, objectVal);
     }
    }
  */
}
