/* connect to http://192.168.4.1 in a web browser
 * to set up WiFi
 */

#include "Config.h"

ESP8266WebServer server(80);

String Config::getValue(int start) {
  String str = "";
  for(int i = start; i < start+128; ++i) {
    str += char(EEPROM.read(i));
  }
  return str;
}

void Config::saveValue(int start, String value) {
  // clearing
  for (int i = start; i < start+128; ++i) { 
    EEPROM.write(i, 0); 
  }
  // writing
  for (int i = start; i < start+value.length(); ++i) { 
    EEPROM.write(i, value[i-start]); 
  }
  EEPROM.commit();
  
}

void Config::handleRoot() {
  _ssid = Config::getValue(EEPROM_SSID);
  _pass = Config::getValue(EEPROM_PASS);
  _lat = Config::getValue(EEPROM_LAT);
  _lon = Config::getValue(EEPROM_LON);

  
  String page = FPSTR(HTTP_START);
  page += FPSTR(SETUP_START);

  //ssid
  String ssid_input = FPSTR(SETUP_INPUT);
  ssid_input.replace("{n}", "SSID");
  ssid_input.replace("{p}", "ssid");
  ssid_input.replace("{v}", _ssid.c_str());

  //pass
  String pass_input = FPSTR(SETUP_INPUT);
  pass_input.replace("{n}", "Passwort");
  pass_input.replace("{p}", "pass");
  pass_input.replace("{v}", _pass.c_str());

  //ssid
  String lat_input = FPSTR(SETUP_INPUT);
  lat_input.replace("{n}", "Latitude");
  lat_input.replace("{p}", "lat");
  lat_input.replace("{v}", _lat.c_str());

  //ssid
  String lon_input = FPSTR(SETUP_INPUT);
  lon_input.replace("{n}", "Longitude");
  lon_input.replace("{p}", "lon");
  lon_input.replace("{v}", _lon.c_str());

  page += ssid_input;
  page += pass_input;
  page += lat_input;
  page += lon_input;
  
  page += FPSTR(SETUP_END);
  page += FPSTR(HTTP_END);
  
  server.send(200, "text/html", page);
}

void Config::handleSave() {
  _ssid = server.arg("ssid").c_str();
  _pass = server.arg("pass").c_str();
  _lat = server.arg("lat").c_str();
  _lon = server.arg("lon").c_str();
  
  Config::saveValue(EEPROM_SSID, _ssid);
  Config::saveValue(EEPROM_PASS, _pass);
  Config::saveValue(EEPROM_LAT, _lat);
  Config::saveValue(EEPROM_LON, _lon);

  String page = FPSTR(HTTP_START);
  page += "Settings saved. Please restart device.";
  page += FPSTR(HTTP_END);
  
  server.send(200, "text/html", page);
}

void Config::begin() {
  EEPROM.begin(512);

  //initial setup
  if(EEPROM.read(385) == 255) {
    Serial.println("DOING INITIAL SETUP");
    Config::saveValue(EEPROM_SSID, "Funkloch");
    Config::saveValue(EEPROM_PASS, "qwertyuiop");
    Config::saveValue(EEPROM_LAT, "52.38335");
    Config::saveValue(EEPROM_LON, "9.744987");
    EEPROM.write(385, 0);
    EEPROM.commit();
  }
}

void Config::startAP(const char* ssid, const char* password) {
  Serial.print("Starting config mode...");
  if(WiFi.status() == WL_CONNECTED) {
    WiFi.disconnect();
  }
//  delay(1000);
  WiFi.mode(WIFI_AP);
  Serial.print("setting up AP...");
  WiFi.softAP(ssid);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", std::bind(&Config::handleRoot, this));
  server.on("/save", std::bind(&Config::handleSave, this));
  server.begin();
  Serial.println("HTTP server started");
};

void Config::loop() {
  server.handleClient();
};

