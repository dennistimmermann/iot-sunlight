
// defines
#define STATE_IDLE 0x600
#define STATE_CONNECTING 0x601
#define STATE_CONFIG 0x602
#define STATE_CONNECTED 0x603
#define STATE_READY 0x604

unsigned long previousMillis = 0;
int ledState = LOW;
int state = STATE_IDLE;

// setting
void setup() {
  // connect to wifi
}

void loop() {
  unsigned long currentMillis = millis();

  if(state == STATE_CONNECTING) {
    if(currentMillis - previousMillis >= 500) {
      previousMillis = currentMillis;
      if(WiFi.status() == WL_CONNECTED) {
        state = STATE_CONNECTED;
      }
      //blink every 500ms
    }
  }

  else if(state == STATE_CONNECTED) {
    api.fetchTime();
    delay(1000);
    api.fetchAPI(config.getValue(EEPROM_LAT), config.getValue(EEPROM_LON));
    state = STATE_READY;
  }

  if(state == STATE_READY) {
    float f = (float)((long)now()-(long)api.sunrise) / (float)(api.sunset-api.sunrise);
    int p = constrain(f*100.0, 0, 100); //percent how much daylight passed
    // update LEDS
  }

  else if(state == STATE_CONFIG) {
    config.loop();
    //blink every 50ms
  }
}
