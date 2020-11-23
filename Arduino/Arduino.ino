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
const long baseValue;
const long reminderValue;
int maxReading;
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
  XMINUTES = setDrinkReminder();
}

void loop() {
  float objectVal = dataR();
  int buttonNew = digitalRead(BUTTON_PIN);
  if(millis() - baseValue >= THIRTYMINUTES) {
     todaysDateFormatted = TodaysDate();
     updateDateServer(todaysDateFormatted);
     baseValue = millis();
  }
  if(millis() - reminderValue >= XMINUTES) {
      blinkReminder();
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
