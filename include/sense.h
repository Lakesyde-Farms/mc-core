#include <Arduino.h>

#ifndef sense_H
#define sense_H
#pragma once

class SensorCL {
  public: 
    float tempSense();
    float humidSense();
    float lightSense();
    float moistureSense();
};

#endif