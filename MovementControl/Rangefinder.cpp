#include "Rangefinder.h"
#include "Arduino.h"
#include "NewPing.h"

Rangefinder::Rangefinder(int triggerPin, int echoPin) {
  this -> triggerPin = triggerPin;
  this -> echoPin = echoPin;
  pinMode(this -> triggerPin, OUTPUT);
  pinMode(this -> echoPin, INPUT);
  NewPing sonar(triggerPin, echoPin, 500);
}

int Rangefinder::getDistance() {
  int distance = this -> calcDistance();
  this -> addToHistory(distance);
  return this -> lowestDistance();
}

int Rangefinder::calcDistance() {
  sonar.ping_in();
}

void Rangefinder::addToHistory(int distanceValue) {
  static int position = 0;
  history[position] = distanceValue;
  position = (position + 1) % historyLength;
}

// Precondition: history has at least one element
int Rangefinder::lowestDistance() {
  int smallest = history[0];
  for(int i = 1; i < historyLength; i++) {
    smallest = smallest < history[i] ? smallest : history[i];
  }
  return smallest;
}
