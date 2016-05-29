#ifndef H_CONFIG
#define H_CONFIG

#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <EEPROM.h>

#define EEPROM_SSID 0
#define EEPROM_PASS 128
#define EEPROM_LAT 256
#define EEPROM_LON 384

const char HTTP_START[] PROGMEM  = "<!DOCTYPE html><html><head><meta charset=\"utf-8\"><title></title><style media=\"screen\">body{font-family:Arial Helvetica,sans-serif;text-align:center;color:#4e4e4e;}*{margin:2px;}</style></head><body>";
const char HTTP_END[] PROGMEM    = "</body></html>";
const char SETUP_START[] PROGMEM  = "<h1>FROM DAWN TILL DUSK</h1><form action=\"save\">";
const char SETUP_INPUT[] PROGMEM  = "<div>{n}</div><input type=\"text\" name=\"{p}\" value=\"{v}\"><br>";
//const char SETUP_INPUT2 PROGMEM  = "</div><input type=\"text\" name=\"";
//const char SETUP_INPUT3 PROGMEM  = "\" value=\"";
//const char SETUP_INPUT4 PROGMEM  = "\"><br>";
//const char SETUP_START[] PROGMEM = "<h1>FROM DAWN TILL DUSK</h1><form action=\"save\">";
const char SETUP_END[] PROGMEM   = "<input type=\"submit\" value=\"SAVE\"></form>";

//ESP8266WebServer server(80);

class Config {
  public:
    void begin();
    void handleRoot();
    void handleSave();
    void startAP(const char* ssid, const char* password);
    void loop();
    String getValue(int start);
    void saveValue(int start, String value);
  private:
    String _ssid = "";
    String _pass = "";
    String _lat = "";
    String _lon = "";
};

#endif H_CONFIG
