#include <Arduino.h>
#include <sense.h>
#include <DHT.h>

#define DHTPIN 1
#define DHTTYPE DHT22

DHT dht = DHT(DHTPIN, DHTTYPE);

float SensorCL::tempSense() {
  return dht.readTemperature();
};

float SensorCL::humidSense(){
  return dht.readHumidity();
};
float SensorCL::lightSense(){
  return analogRead(A0);
};
float SensorCL::moistureSense(){
  return analogRead(A0);
};


