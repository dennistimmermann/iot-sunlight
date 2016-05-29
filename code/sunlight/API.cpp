/* connect to http://192.168.4.1 in a web browser
 * to set up WiFi
 */

#include "API.h"
#include "Config.h"

const char* host = "api.sunrise-sunset.org";
const int port = 80;

size_t API::parseTime(String t) {
  int year = t.substring(0,4).toInt();
  int month = t.substring(5,7).toInt();
  int day = t.substring(8,10).toInt();
  
  int hour = t.substring(11,13).toInt();
  int minute = t.substring(14,16).toInt();
  int second = t.substring(17,19).toInt();
  
  tmElements_t p = {second,minute,hour,0,day,month,year-1970};
  return makeTime(p);
}

int API::getTimezone(String t) {
  int add = t.substring(18,20).toInt();
  if(t[19] == '-') {
    add = add *-1;
  }
  return add;
}

void API::fetchTime() {
  Serial.println("Fetching time...");
  String url = "http://www.timeapi.org/cet/now";
  HTTPClient http;
  http.begin(url);
  int httpCode = http.GET();
  if(httpCode > 0) {
      if(httpCode == 200) {
          String payload = http.getString();
          Serial.println(payload);

          Serial.println("setting time");

          //debug set time to noon
//          size_t t = API::parseTime("2016-05-29T12:12:02+00:00");          
          size_t t = API::parseTime(payload);
          timeOffset = API::getTimezone(payload);
          setTime(t);
      }
  } else {
      Serial.println("[HTTP] GET... failed, error:"); 
      Serial.println(http.errorToString(httpCode).c_str());
  }
  
}

void API::fetchAPI(String lat, String lon) {

  String url = "http://api.sunrise-sunset.org/json?lat={1}&lng={2}&formatted=0";
  url.replace("{1}", lat.c_str());
  url.replace("{2}", lon.c_str());

  HTTPClient http;
  http.begin(url);
  int httpCode = http.GET();
  Serial.print("URL:");
  Serial.print(url);
  Serial.println("Fetching API...");
  if(httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.print("[HTTP] GET... code:");
      Serial.println(httpCode);

      // file found at server
      if(httpCode == 200) {
          String payload = http.getString();
          Serial.println(payload);

          //get sunrise
          int sunrisePos = payload.indexOf("sunrise") + 10; // +10 for chars: sunrise":"
          String sunriseTime = payload.substring(sunrisePos, sunrisePos+25);

          //get sunset
          int sunsetPos = payload.indexOf("sunset") + 9; // +9 for chars: sunset":"
          String sunsetTime = payload.substring(sunsetPos, sunsetPos+25);

          sunrise = API::parseTime(sunriseTime)+(timeOffset*60*60);
          sunset = API::parseTime(sunsetTime)+(timeOffset*60*60);

          Serial.print("SUNRISE: ");
          Serial.println(sunrise);

          Serial.print("NOW:     ");
          Serial.println(now());

          Serial.print("SUNSET:  ");
          Serial.println(sunset);
      }
  } else {
      Serial.println("[HTTP] GET... failed, error:"); 
      Serial.println(http.errorToString(httpCode).c_str());
      Serial.println(http.getString());
  }

  http.end();
}

