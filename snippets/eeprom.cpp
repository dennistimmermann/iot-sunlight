//Defines
#define EEPROM_SSID 0
#define EEPROM_PASS 128
#define EEPROM_LAT 256
#define EEPROM_LON 384

//Init
void Config::begin() {
  EEPROM.begin(512);
}

//Funktionen
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
