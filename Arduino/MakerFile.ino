#include "dateChecker.h"
#include "secret.h"
#include "Firebase_Arduino_WiFiNINA.h"
#include "firebaseConnection.h"
#include "light.h"
#include "HX711.h"
#include "Adafruit_NeoPixel.h"

#define BUTTON_PIN   0

long TENMINUTES = 0;
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

  //maxReading = getMaxWeight();
  scale.tare();
  ColorMe(0, 0, 0);
  setColors();
  delay(2000);
  TENMINUTES = setDrinkReminder();
}

void loop() {
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
    drinkCounter(objectVal, maxReading, todaysDateFormatted);
  }
}
