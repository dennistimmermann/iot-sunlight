#include "Arduino.h"
#include "RGBFade.h"
#include "Part.h"

RGBFade::RGBFade(int count_) {
  count = count_;
  parts = new Part[count];
  
  for ( int i = 0; i < count; i++) {
    parts[i].setRGB(0,0,0);
  }
}

void RGBFade::setPart(int id, int r, int g, int b) {
  if (id <= count) {
    parts[id].setRGB(r, g, b);
  }
}

void RGBFade::update( int pos) {
  if (count > 1) {
    float step = 100/(count-1);

    float start = 0;
    float end = 0;
    int tmpPos = 0;
    int counter = 0;

    float percentStart = 0;
    float percentEnd = 0;
    while ( end < pos) {
      if (start < pos) {
        start = tmpPos-step;
      }
      end = tmpPos;
      tmpPos += step;
      counter++;
    }

    float percent = ((pos-start) * 100) / (end - start);

    percentStart = 0 + (100-percent);
    percentEnd = 100 - (100-percent);

    int startR =  parts[constrain(counter-2, 0, count)].getR() ;
    int endR =    parts[constrain(counter-1, 0, count)].getR() ; 
    startR = int( startR * (percentStart/ 100)); 
    endR = int( endR * (percentEnd/ 100)); 
    masterR = (startR + endR)/2;

    int startG =  parts[constrain(counter-2, 0, count)].getG() ;
    int endG =    parts[constrain(counter-1, 0, count)].getG() ; 
    startG = int( startG * (percentStart/ 100)); 
    endG = int( endG * (percentEnd/ 100)); 
    masterG = (startG + endG)/2;

    int startB =  parts[constrain(counter-2, 0, count)].getB() ;
    int endB =    parts[constrain(counter-1, 0, count)].getB() ; 
    startB = int( startB * (percentStart/ 100)); 
    endB = int( endB * (percentEnd/ 100)); 
    masterB = int((startB + endB)/2);
  }
}

int RGBFade::getR() {
  return masterR;
}
int RGBFade::getG() {
  return masterG;
}
int RGBFade::getB() {
  return masterB;
}
