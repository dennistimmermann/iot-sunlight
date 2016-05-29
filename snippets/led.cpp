#define NUM_LEDS 6
#define DATA_PIN 5

// LED Colors
int r = 0;
int g = 0;
int b = 0;
CRGB leds[NUM_LEDS];

RGBFade value(10);

//SETUP
value.setPart(0,   0,   0,   0);
value.setPart(1,  86, 106, 126);
value.setPart(2, 127, 142, 157);
value.setPart(3, 209, 214, 219);
value.setPart(4, 250, 250, 250);
value.setPart(5, 255, 255, 255);
value.setPart(6, 246, 232, 203);
value.setPart(7, 228, 185,  99);
value.setPart(8, 221, 162,  48);
value.setPart(9,   0,   0,   0);

//LOOP
for ( int j = 0; j < NUM_LEDS; j++) {
	leds[j].r = 0;
	leds[j].g = 0;
	leds[j].b = 0;
}
