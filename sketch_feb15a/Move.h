#ifndef MOVE_H
#define MOVE_H

#include "Convenient.h"

class Adafruit_NeoPixel;

class Move : public Animation
{
private:
  unsigned char cur;
  uint32_t col;
public:
  Move(unsigned char cur) : cur(cur) { ms = 20; }

  bool UpdateFrame(Adafruit_NeoPixel &strip)
  {
    if (cur == NUMLEDS)
    {
      cur = 0;
      if (ms == 10) ms = 0;
    }        
    cur++;
    
    return true;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
  }

  void Render(Adafruit_NeoPixel &strip)
  {
    col = strip.Color(BRIGHTNESS, 0, BRIGHTNESS);
    strip.setPixelColor(cur, col);
  }
};

#endif