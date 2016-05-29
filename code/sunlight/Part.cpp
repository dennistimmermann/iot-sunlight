#include "Arduino.h"
#include "Part.h"

Part::Part(int r_, int g_, int b_) {
    r = r_;
    g = g_;
    b = b_;
}

Part::Part() {
}

void Part::setRGB(int r_, int g_, int b_) {
  r = r_;
  g = g_;
  b = b_;
}


int Part::getR() {
  return r;
}
int Part::getB() {
  return b;
}
int Part::getG() {
  return g;
}
