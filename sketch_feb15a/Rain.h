#ifndef RAIN_H
#define RAIN_H

#include "Convenient.h"

class Adafruit_NeoPixel;

class Rain : public Animation
{
  short start, end;
  RGB rgb;
  short cur;
  bool dir = true;

public:
  Rain(int start, int end, const RGB &rgb) : start(start), end(end), rgb(rgb), cur(start)
  {    
    ms = rand() % 40;
  }

  bool UpdateFrame(Adafruit_NeoPixel &strip)
  {
    bool fwd = end > start;
    
    cur += fwd ? 1 : -1;
    
    if (dir && (fwd ? cur >= end : cur < end)) 
    {
      cur = start; 
      dir = false; 
    }
    return dir || (fwd ? cur < end : cur >= end);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
  }

  void Render(Adafruit_NeoPixel &strip)
  {
    bool fwd = end > start;
    
    if (dir)
    {
      for (int i = start; fwd ? i < cur : i >= cur; i += fwd ? 1 : -1)
      {       
        strip.setPixelColor(i, strip.Color(rgb.r, rgb.g, rgb.b)); 
      }
    }    
    else
    {
      for (int i = cur; fwd ? i < end : i >= end; i += fwd ? 1 : -1)
      {
          strip.setPixelColor(i, strip.Color(rgb.r, rgb.g, rgb.b));
      }
    }
  }
};

#endif
