/**
 * BasicHTTPClient.ino
 *
 *  Created on: 24.05.2015
 *
 */

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#define USE_SERIAL Serial

#define mote      "esp32"
#define location  "318(A)" 

WiFiMulti wifiMulti;
String url = "http://192.168.xxx.xxx/atalFdp/serverRoom.php";

unsigned long lastTime = 0;
unsigned long timerDelay = 2000;// Set timer to 5 seconds (5000)

// Variables
float temperature=84.4, humidity=46.9;
bool doorStatus=0;

#include "DHT.h"
#define DHTPIN 4     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
    USE_SERIAL.begin(115200);
    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();
    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }
    wifiMulti.addAP("ssid1", "pwd1");
    wifiMulti.addAP("ssid2", "pwd2");
    dht.begin();
    setupOled();
      humidity = dht.readHumidity();
      // Read temperature as Celsius (the default)
      temperature = dht.readTemperature();
    updateOled();
}

void loop() {
   //Send an HTTP POST request every 10 minutes
  if ((millis() - lastTime) > timerDelay) {
    // wait for WiFi connection

      // Reading temperature or humidity takes about 250 milliseconds!
      // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
      humidity = dht.readHumidity();
      // Read temperature as Celsius (the default)
      temperature = dht.readTemperature();
        
      updateOled();

    if((wifiMulti.run() == WL_CONNECTED)) {
      
        HTTPClient http;

        USE_SERIAL.print("[HTTP] begin...\n");
        // configure traged server and url
        http.begin(url); //HTTP

      
        // Specify content-type header
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");
        //http.addHeader("Content-Type", "application/json");
        //http.addHeader("Content-Type", "text/plain");

        // Data to send with HTTP POST
        String httpRequestData = "api_key=tPmAT5Ab3j7F9&mote=";
        httpRequestData +=mote;
        httpRequestData +="&location=";
        httpRequestData +=location;
        httpRequestData +="&temperature=";
        httpRequestData +=String(temperature);
        httpRequestData +="&humidity=";
        httpRequestData +=String(humidity);
        httpRequestData +="&doorStatus=";
        httpRequestData +=String(doorStatus); 
                  
//        String httpRequestData = "{\"api_key\":\"tPmAT5Ab3j7F9\",\"sensor\":\"BME280\",\"value1\":\"24.25\",\"value2\":\"49.54\",\"value3\":\"1005.14\"}";
//        String httpRequestData = "Hello, World!";

//        USE_SERIAL.print("[HTTP] POST...\n");
        // Send HTTP POST request
        int httpCode = http.POST(httpRequestData);

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
//            USE_SERIAL.printf("[HTTP] POST... code: %d\n", httpCode);
            httpRequestData  ="temperature=";
            httpRequestData +=String(temperature);
            httpRequestData +=" humidity=";
            httpRequestData +=String(humidity);
            USE_SERIAL.println(httpRequestData);
            // file found at server
//            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                USE_SERIAL.println(payload);
//            }
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }
    lastTime = millis();
  }
}
