#include "HX711.h"
const int LOADCELL_DOUT_PIN = 3;
const int LOADCELL_SCK_PIN = 2;

HX711 scale;


float calibration_factor = -424;
float units;
float ounces;



void setp(){
  Serial.println("HX711 weighing");
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor);
  Serial.println("Readings:");
}

int dataR() {
   units = scale.get_units(),10;
   if (units < 2.50) {
    return 0.00;
  } else { 
   return units;
}
}
