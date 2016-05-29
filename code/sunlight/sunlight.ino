/*


/* Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */

// includes
#include <ESP8266WiFi.h>
#include <TimeLib.h>
#include "Config.h"
#include "API.h"
#include "RGBFade.h"
#include "FastLED.h"

// setting up state machine
#define STATE_IDLE 0x600
#define STATE_CONNECTING 0x601
#define STATE_CONFIG 0x602
#define STATE_CONNECTED 0x603
#define STATE_READY 0x604

unsigned long previousMillis = 0;
int ledState = LOW;
int state = STATE_IDLE;

// setting up LEDS
#define NUM_LEDS 6
#define DATA_PIN 5

// LED Colors
int r = 0;
int g = 0;
int b = 0;
CRGB leds[NUM_LEDS];

// fade steps
RGBFade value(10);

Config config;
API api;

// start setup function
void startSetup() {
  state = STATE_CONFIG;
  digitalWrite(LED_BUILTIN, LOW);
  config.startAP("ESP12", "12345678");
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  // setup FastLED and colors throughout day
  //            ID   R    G    B
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
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);

  // attach config mode to button
  attachInterrupt(0, startSetup, RISING);
  
  Serial.begin(115200);
  delay(1000);
  Serial.println("Welcome to From Dawn Till Dusk :)");

  // Stationary mode
  WiFi.mode(WIFI_STA);
  config.begin();
  delay(1000);
  
  // try to connect to WiFi
  Serial.println("getting saved WiFi credentials...");
  String ssid = config.getValue(EEPROM_SSID);
  String pass = config.getValue(EEPROM_PASS);
  Serial.print("SSID:");
  Serial.println(ssid);
  Serial.print("PASS:");
  Serial.println(pass);

  if(ssid[0] == 255) {
    Serial.println("wat");
  }
  

  if(ssid.length() > 1 && ssid[0] != 0) {
    state = STATE_CONNECTING;
    Serial.println("...connecting");
    WiFi.begin(ssid.c_str(), pass.c_str());
  }
  Serial.println();
  
}

void loop() {
  unsigned long currentMillis = millis();
  
  if(state == STATE_CONNECTING) {
    if(currentMillis - previousMillis >= 500) {
      previousMillis = currentMillis;  
      if(WiFi.status() == WL_CONNECTED) {
        Serial.println("successfully connected");
        state = STATE_CONNECTED;
        ledState = HIGH;
      }
      if (ledState == LOW)
        ledState = HIGH;  // Note that this switches the LED *off*
      else
        ledState = LOW;   // Note that this switches the LED *on*
      digitalWrite(LED_BUILTIN, ledState);
    }
  }

  else if(state == STATE_CONNECTED) {
    digitalWrite(LED_BUILTIN, LOW);
    api.fetchTime();
    delay(1000);

    String lat = config.getValue(EEPROM_LAT);
    String lon = config.getValue(EEPROM_LON);
    Serial.println(lat);
    Serial.println(lon);
    api.fetchAPI(lat, lon);
    state = STATE_READY;
  }

  if(state == STATE_READY) {
    // calculate sun progress throughout the day
    float f = (float)((long)now()-(long)api.sunrise) / (float)(api.sunset-api.sunrise);
    int p = constrain(f*100.0, 0, 100);
//    Serial.println(p);

    if(currentMillis - previousMillis >= 1000) {
      previousMillis = currentMillis; 
      Serial.println("refreshing sunset times");
      Serial.println(p);
      state == STATE_CONNECTED;
    }

    // update LEDs
    value.update(p);
    for ( int j = 0; j < NUM_LEDS; j++) {
      if(p > 0 && p < 100) {
        leds[j].r = value.getG();
        leds[j].g = value.getR();
        leds[j].b = value.getB();
      } else {
        leds[j].r = 0;
        leds[j].g = 0;
        leds[j].b = 0;
      }
      
    }
    FastLED.show();
  }

  else if(state == STATE_CONFIG) {
    config.loop();
    if(currentMillis - previousMillis >= 50) {
      previousMillis = currentMillis;  
      if (ledState == LOW)
        ledState = HIGH;  // Note that this switches the LED *off*
      else
        ledState = LOW;   // Note that this switches the LED *on*
      digitalWrite(LED_BUILTIN, ledState);
    }
  }
}
