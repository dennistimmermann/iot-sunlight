/*
  Fromt Dawn Till Dusk
  project by Robert Schnüll & Dennis Timmermann
             http://interaktives.design
             http://tmrmn.com
*/
#include "RGBFade.h"
#include "FastLED.h"


#define NUM_LEDS 6
#define DATA_PIN 5


RGBFade value(5);
int r = 0;
int g = 0;
int b = 0;

CRGB leds[NUM_LEDS];


void setup() {

  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);

  //            ID   R    G    B
  value.setPart(0,   0,   0, 255);
  value.setPart(1,   0, 255, 255);
  value.setPart(2, 255, 255,   0);
  value.setPart(3, 255,   0,   0);
  value.setPart(4, 125,   0, 125);
}

void loop() {



  for ( int i = 1; i < 100; i++) {
    value.update(i);
    for ( int j = 0; j < NUM_LEDS; j++) {
      leds[j].r = value.getG();
      leds[j].g = value.getR();
      leds[j].b = value.getB();
    }
    FastLED.show();

    delay(50);
  }

  for ( int i = 100; i > 1; i--) {
    value.update(i);
    for ( int j = 0; j < NUM_LEDS; j++) {
      leds[j].r = value.getG();
      leds[j].g = value.getR();
      leds[j].b = value.getB();
    }
    FastLED.show();

    delay(50);
  }




}
