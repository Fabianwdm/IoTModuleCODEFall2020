#include "HX711.h"
#define BUTTON_PIN  2
const int LOADCELL_DOUT_PIN = 3;
const int LOADCELL_SCK_PIN = 2;


HX711 scale;


float calibration_factor = -423;
float units;
int buttonState = 0;
units = scale.get_units(),10;

void setupWeight(){
      Serial.begin(9600);
  Serial.println("HX711 weighing");
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor);
  scale.tare();
  Serial.println("Readings:");
}

void loop() {
  Serial.print("Reading:");
  if (units < 2) {
    units = 0.00; }
  delay(1000);
}

void currentWeightValue(){
    return units;
}