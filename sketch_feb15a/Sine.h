#ifndef SINE_H_
#define SINE_H_

#include <Adafruit_NeoPixel.h>
#include "AnimList.h"
#include "Convenient.h"

class Adafruit_NeoPixel;

class Sine : public Animation
{
private:
  unsigned char start = 0, range = 10;
  uint32_t col;
public:
  Sine() { ms = 0; }

  bool UpdateFrame(Adafruit_NeoPixel &strip) 
  { 
    return true; 
  }

  void Render(Adafruit_NeoPixel &strip)
  {
    long frame = millis() / 2;  
    uint32_t col = abs(sin(DEG2RAD(frame)) * 5.f);
    col = strip.Color(col, 0, col);

    int num = strip.numPixels() / 5;

    for (int  i = 0; i < num; i++)
    {
      strip.setPixelColor(i, col);
    }
  }
};

#endif
