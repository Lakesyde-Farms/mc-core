#include <sense.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22

uint8_t A3;
uint8_t A0;

DHT dht = DHT(DHTPIN, DHTTYPE);

class SensorCL {
  public:
    float tempSense(){
      return dht.readTemperature();
    };
    float humidSense(){
      return dht.readHumidity();
    };
    float lightSense(){
      return analogRead(A0);
    };
    float moistureSense(){
      return analogRead(A3);
    };
};