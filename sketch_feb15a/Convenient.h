#ifndef CONVENIENT_H
#define CONVENIENT_H

struct RGB
{
  char r,g,b;
};

#define DEG2RAD(deg) ((deg) * (PI/180))
#define NUMLEDS 144
#define BRIGHTNESS ((char)((rand() % 5)+5))

#endif
