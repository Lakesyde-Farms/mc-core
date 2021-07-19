#include <Arduino.h>

#include <ESP8266WiFi.h>

#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>

#ifndef STASSID
#define STASSID "hp-envy"
#define STAPSK  "alpacahollows"
#endif


#define MANUAL_SIGNING 1

const char pubkey[] PROGMEM = R"EOF(
-----BEGIN PUBLIC KEY-----
MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA3sOY4nSqtEUT7WUTdbbp
EvvtZMcS17BFHB4r6IhY3484nNcp0gu7ci0zzbFz5RdBsuMiZ6mejPwX+X5mN8GU
8yl27bcFM16n5LUaXOlBhksoiINc3+sx1ITDyOJDeL0HvmtdDGiDwDTyJZl8y3IB
BD32eDOxqbIfTtLvHi1nJC9zUC8qSa5Wh0jxDun0ZdS/MwpWbo3wsUV6Uhkzqrfs
0AVyzbdh8+eLLDK1SYiAOkNCYLFw+FKw1oYY9SeamEd01YodAGCaic5olj1d0eJM
PrdKKZEsSqnKOvGMw5CyvSv6rNpnrR3p6JxY52SR4FFgx92OAjD0bq0RamETy6hU
iQIDAQAB
-----END PUBLIC KEY-----
)EOF";

#if MANUAL_SIGNING
BearSSL::PublicKey *signPubKey = nullptr;
BearSSL::HashSHA256 *hash;
BearSSL::SigningVerifier *sign;
#endif

void update() {
  #if MANUAL_SIGNING
  signPubKey = new BearSSL::PublicKey(pubkey);
  hash = new BearSSL::HashSHA256();
  sign = new BearSSL::SigningVerifier(signPubKey);
  #endif

  WiFiClient client;

  #if MANUAL_SIGNING
  // Ensure all updates are signed appropriately.  W/o this call, all will be accepted.
  // Disabled until signing ci integrated

  // Update.installSignature(hash, sign);
  #endif
  // If the key files are present in the build directory, signing will be
  // enabled using them automatically

  ESPhttpUpdate.setLedPin(LED_BUILTIN, LOW);

  // Pending update of mc server
  t_httpUpdate_return ret = ESPhttpUpdate.update(client, "path to bin");

  switch (ret) {
    case HTTP_UPDATE_FAILED:
      Serial.printf("HTTP_UPDATE_FAILED Error (%d): %s\n", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
      break;

    case HTTP_UPDATE_NO_UPDATES:
      Serial.println("HTTP_UPDATE_NO_UPDATES");
      break;

    case HTTP_UPDATE_OK:
      Serial.println("HTTP_UPDATE_OK");
      break;
  }

  delay(10000);
}
