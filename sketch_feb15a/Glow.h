#ifndef GLOW_H
#define GLOW_H

#include "Convenient.h"

class Adafruit_NeoPixel;

class Glow : public Animation
{
  short start, end;
  const RGB col;
  int deg = 1;
public:
  Glow(short start, short end, const RGB &rgb) : col(rgb), start(start), end(end)
  {
    ms = 5;
  }

  bool UpdateFrame(Adafruit_NeoPixel &strip)
  {
    return true;
  }

  void Render(Adafruit_NeoPixel &strip)
  {
    bool fwd = end > start;

    RGB rgb;
    rgb.r = (int)fabs((sin(DEG2RAD(millis() / 10)) * col.r));
    rgb.g = (int)fabs((sin(DEG2RAD(millis() / 10)) * col.g));
    rgb.b = (int)fabs((sin(DEG2RAD(millis() / 10)) * col.b));
    
    for (int i = start; fwd ? i < end : i >= end; i += fwd ? 1 : -1)
    {      
      strip.setPixelColor(i, strip.Color(rgb.r, rgb.g, rgb.b)); 
    }
  }
};

#endif
