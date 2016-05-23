#include <ESP8266WiFi.h>          //ESP8266 Core WiFi Library (you most likely already have this in your sketch)
#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>

void setup() {
  // put your setup code here, to run once:
  WiFiManager wifiManager;

  wifiManager.setAPCallback(configModeCallback);
  wifiManager.setSaveConfigCallback(saveConfigCallback);
  
  wifiManager.autoConnect("IOT-SUNLIGHT");
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
                                    // but actually the LED is on; this is because 
                                    // it is acive low on the ESP-01)
  delay(1000);                      // Wait for a second
  digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(2000); 
}

// code below doesn't work yet
void configModeCallback (WiFiManager *myWiFiManager) {
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  Serial.println(myWiFiManager->getConfigPortalSSID());
}

//void saveConfigCallback () {
//  Serial.println("Should save config");
//  digitalWrite(LED_BUILTIN, LOW);
//}
