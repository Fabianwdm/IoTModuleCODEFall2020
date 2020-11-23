#include "dateChecker.h"
#include "secret.h"
#include "Firebase_Arduino_WiFiNINA.h"
#include "firebaseConnection.h"
#include "light.h"
#include "HX711.h"
#include "Adafruit_NeoPixel.h"

#define BUTTON_PIN   0

long DRINKTIMER;
long THIRTYMINUTES = 1800000;
long baseValue;
long reminderValue;
int maxReading = 1000;
int buttonNew = digitalRead(BUTTON_PIN);
float oldObjectVal;
float previousValue;
String todaysDateFormatted;


void setup() {
  Serial.begin(9600);
  pinMode(PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  strip.setBrightness(100);
  theaterChase(strip.Color(127, 127, 127), 50, 20);
  firebaseSetup();
  todaysDateFormatted = TodaysDate();
  updateDateServer(todaysDateFormatted);
  setupWeight();
  maxReading = getMaxWeight();
  scale.tare();
  ColorMe(0, 0, 0);
  setColors();
  delay(2000);
  DRINKTIMER = setDrinkReminder();
}

void loop() {
    float objectVal = dataR();
    if (millis() - baseValue >= THIRTYMINUTES){
      todaysDateFormatted = TodaysDate();
      updateDateServer(todaysDateFormatted);
      baseValue = millis();
  }

  if (millis() - reminderValue >= DRINKTIMER){
      blinkReminder(objectVal, objectVal);
      reminderValue = millis();
  }
  
  if (buttonNew == 1) {
    maxReading = maxData();
    delay(500);
    updateMaxWeight(maxReading);
  }

  colorSetter(objectVal, maxReading);
  
  if (objectVal < (maxReading * 0.98)) {
    float objectVal = dataR();
    drinkCounter(objectVal, maxReading, todaysDateFormatted);
  }
}
