#ifndef H_PART
#define H_PART

#include "Arduino.h"

class Part
{
  public:
    Part(int r, int g, int b);
    Part();

    void setRGB(int r_,int g_, int b_);
    int getR();
    int getG();
    int getB();
    
  private:
    int r;
    int g;
    int b;
};

#endif
