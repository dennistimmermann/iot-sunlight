#ifndef H_API
#define H_API

#include "Arduino.h"
#include <TimeLib.h>
#include <WiFiClient.h> 
#include <ESP8266HTTPClient.h>

class API {
  public:
    size_t parseTime(String t);
    int getTimezone(String t);
    void fetchAPI(String lat, String lon);
    void fetchTime();
    int timeOffset = 0;
    size_t sunrise = 0;
    size_t sunset = 1;
  private:

};

#endif H_API
