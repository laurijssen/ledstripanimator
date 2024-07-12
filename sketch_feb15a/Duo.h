#ifndef DUO_H
#define DUO_H

#include "Convenient.h"
#include "AnimList.h"

class Adafruit_NeoPixel;

class Duo : public Animation
{
private:
  unsigned char cur;
public:
  Duo(unsigned char cur) : cur(cur) { ms = 100; }

  bool UpdateFrame(Adafruit_NeoPixel &strip)
  {    
    if (cur == NUMLEDS)
    {
      cur = 0;
      if (ms == 10) ms = 0;
    }        
    cur+=2;
    
    return true;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
  }

  void Render(Adafruit_NeoPixel &strip)
  {
    uint32_t col = strip.Color(10, 0, 10);
    for (int i = 0; i < 2; i++)
      strip.setPixelColor(cur+i, col);
  }
};

#endif
