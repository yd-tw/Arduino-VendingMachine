#ifndef HCSR04_h
#define HCSR04_h

#include "Arduino.h"

class HCSR04 {
  public:
    HCSR04(int trigPin, int echoPin);
    void begin();
    int distance();

  private:
    int _trigPin;
    int _echoPin;
};

#endif
