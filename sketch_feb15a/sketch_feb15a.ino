#include <Adafruit_NeoPixel.h>
#include "Duo.h"
#include "Sine.h"
#include "Rain.h"
#include "Move.h"
#include "Glow.h"
#include "AnimList.h"
#include "Convenient.h"

#define NUMLEDS 144
#define BRIGHTNESS ((char)((rand() % 5)+5))

AnimList *list;

Move m1(0);
Move m2(70);
Sine s;
//Rain r1(0, 30, {BRIGHTNESS, 0, BRIGHTNESS }) ;
//Rain r2(40, 80, {BRIGHTNESS, BRIGHTNESS, 0 }) ;
//Rain r3(90, 120, {0, BRIGHTNESS, BRIGHTNESS }) ;
//Rain r4(90, 120, {0, BRIGHTNESS, BRIGHTNESS }) ;

//Glow glow(0, 50, RGB{0, 0, 10});
//Glow glow2(50, 100, RGB{10, 0, 10});

Duo m(0);

void setup() {
  list = new AnimList(NUMLEDS);  
  //list->AddFirst(&glow);
  //list->Add(&glow2);
  //list->AddFirst(&m);
  //list->AddFirst(&s);
  list->Add(&m1);
  list->Add(&m2);
  //list->Add(&s);
}

void loop() {   
  list->UpdateFrame();
  list->Render();

  /*if (!list->Find(&r1))
  {
    r1 = Rain (rand() % NUMLEDS, rand() % NUMLEDS, {BRIGHTNESS, 0, 15 }) ;
    list->AddFirst(&r1);
  } 
  if (!list->Find(&r2))
  {
    r2 = Rain(rand() % NUMLEDS, rand() % NUMLEDS, {0, BRIGHTNESS, 0 }) ;
    list->AddFirst(&r2);
  }
  if (!list->Find(&r3))
  {
    r3 = Rain(rand() % NUMLEDS, rand() % NUMLEDS, {0, 0, BRIGHTNESS }) ;
    list->AddFirst(&r3);
  }
  if (!list->Find(&r4))
  {
    r4 = Rain(rand() % NUMLEDS, rand() % NUMLEDS, {BRIGHTNESS, BRIGHTNESS, BRIGHTNESS }) ;
    list->AddFirst(&r4);
  }*/
}
