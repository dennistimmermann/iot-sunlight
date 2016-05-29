
// Stationary mode
WiFi.mode(WIFI_STA);

String ssid = config.getValue(EEPROM_SSID);
String pass = config.getValue(EEPROM_PASS);

if(ssid.length() > 1 && ssid[0] != 0) {
state = STATE_CONNECTING;
WiFi.begin(ssid.c_str(), pass.c_str());
}
