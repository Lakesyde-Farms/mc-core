#include <Arduino.h>
#include <ArduinoJson.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>

HTTPClient https;

const uint8_t fingerprint[20] = {0x76, 0xA5, 0x74, 0x11, 0x63, 0xC3, 0xCA, 0xED, 0x2F, 0x7D, 0xEC, 0x88, 0x20, 0x2D, 0xC7, 0xEC, 0xA3, 0x0F, 0x9D, 0xD0};

std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);


void GET () {
  client->setFingerprint(fingerprint);

  Serial.print("[HTTPS] begin...\n");

  if (https.begin(*client, "https://ls-routing.herokuapp.com/api/records?id=prod_9")) {

    Serial.print("[HTTPS] GET...\n");
    // start connection and send HTTP header
    int httpCode = https.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        String payload = https.getString();
        Serial.println(payload );
      }
    } else {
      Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
    }

    https.end();
  } else {
    Serial.printf("[HTTPS] Unable to connect\n");
  }

  Serial.println("Wait 10s before next round...");
  delay(10000);
}

void POST (String payload) {
  client->setFingerprint(fingerprint);

  Serial.print("[HTTPS] begin...\n");

  if (https.begin(*client, "https://ls-routing.herokuapp.com/api/report")) {

    https.addHeader("Content-Type", "application/json");
    
    Serial.print("[HTTPS] POST...\n");
    // start connection and send HTTP header
    int httpCode = https.POST(payload);

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTPS] POST... code: %d\n", httpCode);

      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        String payload = https.getString();
        Serial.println(payload );
      }
      else {
        String payload = https.getString();
        Serial.println("Error response"+payload);
      }
    } else {
      Serial.printf("[HTTPS] POST... failed, error: %s\n", https.errorToString(httpCode).c_str());
    }

    https.end();
  } else {
    Serial.printf("[HTTPS] Unable to connect\n");
  }

  Serial.println("Wait 10s before next round...");
  delay(10000);
  

}
