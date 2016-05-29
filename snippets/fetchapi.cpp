void API::fetchAPI(String lat, String lon) {

  String url = "http://api.sunrise-sunset.org/json?lat={1}&lng={2}&formatted=0";
  url.replace("{1}", lat.c_str());
  url.replace("{2}", lon.c_str());

  HTTPClient http;
  http.begin(url);
  int httpCode = http.GET();

  if(httpCode == 200) {
	  String payload = http.getString();

	  //get sunrise
	  int sunrisePos = payload.indexOf("sunrise") + 10; // +10 for chars: sunrise":"
	  String sunriseTime = payload.substring(sunrisePos, sunrisePos+25);

	  //get sunset
	  int sunsetPos = payload.indexOf("sunset") + 9; // +9 for chars: sunset":"
	  String sunsetTime = payload.substring(sunsetPos, sunsetPos+25);

	  sunrise = API::parseTime(sunriseTime)+(timeOffset*60*60);
	  sunset = API::parseTime(sunsetTime)+(timeOffset*60*60);

	} else {
	  Serial.println(http.errorToString(httpCode).c_str());
	  Serial.println(http.getString());
	}
}
