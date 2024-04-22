#include "HCSR04.h"

HCSR04::HCSR04(int trigPin, int echoPin) {
  _trigPin = trigPin;
  _echoPin = echoPin;
}

void HCSR04::begin() {
  pinMode(_trigPin, OUTPUT);
  pinMode(_echoPin, INPUT);
}

int HCSR04::distance() {
  digitalWrite(_trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigPin, LOW);

  return pulseIn(_echoPin, HIGH) / 29.41 / 2.00;
}
