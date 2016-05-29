void Config::handleRoot() {
  // generate HtML Page
  server.send(200, "text/html", page);
}

void Config::handleSave() {
  _ssid = server.arg("ssid").c_str();
  _pass = server.arg("pass").c_str();
  _lat = server.arg("lat").c_str();
  _lon = server.arg("lon").c_str();

  //save to eeprom
  server.send(200, "text/html", page);
}

void Config::startAP(const char* ssid, const char* password) {

  if(WiFi.status() == WL_CONNECTED) {
    WiFi.disconnect();
  }

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);

  server.on("/", std::bind(&Config::handleRoot, this));
  server.on("/save", std::bind(&Config::handleSave, this));
  server.begin();
};

void Config::loop() {
  server.handleClient();
};
