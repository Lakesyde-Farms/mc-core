#include <Arduino.h>
#include <http.h>
#include <sense.h>
#include <update.h>

#include <ESP8266WiFi.h>

#include <ESP8266WiFiMulti.h>
#include <ArduinoJSON.h>

ESP8266WiFiMulti WiFiMulti;

StaticJsonDocument<256> doc;

JsonObject sensors = doc.createNestedObject("sensors");

SensorCL ssl;


void setup() {
  Serial.begin(9600);
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("hp-envy", "alpacahollows");

  doc["board_id"] = "dev_10";

}

void loop() {
  String output;

  // sensors["temp"] = ssl.tempSense();
  // sensors["humidity"] = ssl.humidSense();
  // sensors["light"] = ssl.lightSense();

  sensors["temp"] = 43;
  sensors["humidity"] =  43;
  sensors["light"] =  43;

  serializeJsonPretty(doc, output);

  Serial.print(output);
  Serial.print(" ");
  Serial.print("\n");

  if ((WiFiMulti.run() == WL_CONNECTED)) {
    POST(output);
  }
  delay(5000);
  update();
  delay(1000);
}

