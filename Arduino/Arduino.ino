#include "dateChecker.h"
#include "secret.h"
#include "Firebase_Arduino_WiFiNINA.h"
#include "firebaseConnection.h"
#include "light.h"
#include "HX711.h"
#include "Adafruit_NeoPixel.h"

#define BUTTON_PIN   0

long XMINUTES;
long THIRTYMINUTES = 1800000;
long baseValue;
long reminderValue;
int maxReading;
float oldObjectVal;
float previousValue;
String todaysDateFormatted;


void setup() {
  Serial.begin(9600);
  pinMode(PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  strip.setBrightness(255);
  theaterChase(strip.Color(127, 127, 127), 50, 20);
  firebaseSetup();
  todaysDateFormatted = TodaysDate();
  updateDateServer(todaysDateFormatted);
  setupWeight();
  maxReading = getMaxWeight();
  scale.tare();
  setColors();
  XMINUTES = setDrinkReminder();
  delay(2000);
  ColorMe(0, 0, 0);
}

void loop() {
  float objectVal = dataR();
  int buttonNew = digitalRead(BUTTON_PIN);
  //Checks and uploads new data if needed every 30 minutes.
  if(millis() - baseValue >= THIRTYMINUTES) {
     todaysDateFormatted = TodaysDate();
     updateDateServer(todaysDateFormatted);
     baseValue = millis();
  }

  //reminds users to drink based on time set.
  if(millis() - reminderValue >= XMINUTES && objectVal > 10) {
      blinkReminder(objectVal, objectVal);
      reminderValue = millis();
  }
  //if button is press set max Weight used to without application.
  if (buttonNew == 1) {
    maxReading = maxData();
    delay(500);
    updateMaxWeight(maxReading);
  }
  //Sets LED color ring.
   colorSetter(objectVal, maxReading);
//Updates drink counter if requirements are met.
  if (objectVal < (maxReading * 0.98)) {
    float objectVal = dataR();
    drinkCounter(objectVal, maxReading, todaysDateFormatted);
  }
}
