#include "TESTsecret.h"
#include "Firebase_Arduino_WiFiNINA.h"
#include "TESTfirebaseConnection.h"
#include "TESTlight.h"
#include "HX711.h"
#include "Adafruit_NeoPixel.h"

#define TENMINUTES (60*1000L) // ten minutes are 600000 milliseconds
float previousValue;
String empty = "Sarah/hexempty";
String full = "Sarah/hexfull";
String reminder = "Sarah/hexreminder";


void setup() {
  strip.setBrightness(255); 
  pinMode(led1, OUTPUT);
  theaterChase(strip.Color(127, 127, 127), 50, 20);
  Serial.begin(9600);
  delay(100); 
  Serial.println();
  firebaseSetup();
  setp();
  scale.tare();
  ColorMe(0,0,0);
  delay(2000);
  setEmptyCup(empty);
  setEmptyCup(full);
  setEmptyCup(reminder);
  giveMeInformation();
  }


unsigned long last10Minutes;

 void loop() {
    float objectVal = dataR();
    if (millis()-last10Minutes >= TENMINUTES){
      last10Minutes+=TENMINUTES;
      Serial.println("One Minutes Has Passed");
    }
    //updateWeight(objectVal);
    //weightColor(objectVal);
    //Serial.println(objectVal);
    /*
    float val = testValue();
    weightColor(objectVal);
    updateWeight(objectVal);
    val = Firebase.getInt(firebaseData, "_CONFIG/WEIGHT");
    Serial.println(val); */
    //testInt();
    //testFloat("testFloat");
  }
