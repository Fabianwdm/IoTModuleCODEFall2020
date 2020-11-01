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


void ColorMe(int R,int G,int B) {
     for(int i=0;i<NUM_LEDS;i++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    strip.setPixelColor(i, strip.Color(R,G,B)); // Moderately bright green color.
  strip.show(); // This sends the updated pixel color to the hardware
}
}
