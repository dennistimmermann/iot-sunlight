#ifndef H_RGBFADE
#define H_RGBFADE

#include "Arduino.h"
#include "Part.h"

class RGBFade
{
  public:
    RGBFade(int count);
    
    void setPart(int id, int r, int g, int b);
    void update(int pos);
    int getR();
    int getG();
    int getB();
    
  private:
    int count;
    int masterR, masterG, masterB;
    Part *parts;

};

#endif
