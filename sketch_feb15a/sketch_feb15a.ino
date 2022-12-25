#include <Adafruit_NeoPixel.h>

#define NUMLEDS 144
#define BRIGHTNESS ((char)((rand() % 5)+5))

#define DEG2RAD(deg) ((deg) * (PI/180))

class Animation
{
  friend class AnimList;

private:
  Animation * next = NULL;
protected:
  uint32_t ms = 0;
  uint32_t last;

public:
  Animation()
  {
    last = millis();
  }

  virtual bool UpdateFrame(Adafruit_NeoPixel &strip) = 0;
  virtual void Render(Adafruit_NeoPixel &strip) = 0;
};

class AnimList
{
  Animation *first = NULL;
  Adafruit_NeoPixel strip;

public:
  AnimList(int nleds) : strip(nleds, 9, NEO_GRB + NEO_KHZ800)
  {
    strip.begin();
  }

  void Add(Animation *a)
  {
    a->next = nullptr;
    
    Animation **anim = &first;

    while (*anim)
      anim = &(*anim)->next;

    *anim = a;
  }

  void AddFirst(Animation *a)
  {
    a->next = first;
    first = a;
  }

  void AddAfter(Animation *a, Animation *after)
  {
    Animation **anim = &first;

    while (*anim)
    {
      if (*anim == after)
      {
        a->next = after->next;
        (*anim)->next = a;
        break;
      }
      anim = &(*anim)->next;
    }
  }

  void Render()
  {
    Animation *a = first;

    while (a)
    {
      a->Render(strip);
      a = a->next;
    }
    
    strip.show();
  }

  void UpdateFrame()
  {
    strip.clear();
    
    Animation **anim = &first;

    while (*anim)
    {
      if (millis() - (*anim)->last >= (*anim)->ms)
      {
        if (!(*anim)->UpdateFrame(strip))
        {
          *anim = (*anim)->next;
        }
        else
        {
          (*anim)->last = millis();
          anim = &(*anim)->next;
        }
      }
    }
  }

  bool Find(Animation *find)
  {
    Animation *anim = first;

    while (anim)
    {
      if (anim == find) return true;

      anim = anim->next;
    }
    return false;
  }

  int Count()
  {
    int c = 0;
    Animation *anim = first;

    while (anim)
    {
      c++;
      anim = anim->next;
    }

    return c;
  }
};

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
    col = strip.Color(0, 0, BRIGHTNESS);
    strip.setPixelColor(cur, col);
  }
};

class Duo : public Animation
{
private:
  unsigned char cur;
  uint32_t col;
  char r = 0,b = 0;
public:
  Duo(unsigned char cur) : cur(cur) { ms = 100; }

  bool UpdateFrame(Adafruit_NeoPixel &strip)
  {    
    if (cur == NUMLEDS)
    {
      cur = 0;
      if (ms == 10) ms = 0;
    }        
    cur+=4;
    
    return true;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
  }

  void Render(Adafruit_NeoPixel &strip)
  {
    col = strip.Color(r++, 0, b+=2);
    for (int i = 0; i < 4; i++)
      strip.setPixelColor(cur+i, col);
  }
};

class Sine : public Animation
{
private:
  unsigned char start = 0, range = 10;
  uint32_t col;
public:
  Sine() { ms = 0; }

  bool UpdateFrame(Adafruit_NeoPixel &strip)
  {      
    return true;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   }

  void Render(Adafruit_NeoPixel &strip)
  {
    long frame = millis() / 10;  
    col = strip.Color(0, abs(sin(DEG2RAD(frame)) * 5.f), 0);
    for (int  i = 0; i < NUMLEDS; i++)
    {
      strip.setPixelColor(i, col);
    }
  }
};

struct RGB
{
  char r,g,b;
};

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

AnimList *list;

Move m1(0);
Move m2(70);
//Sine s;
Rain r1(0, 30, {BRIGHTNESS, 0, BRIGHTNESS }) ;
Rain r2(40, 80, {BRIGHTNESS, BRIGHTNESS, 0 }) ;
Rain r3(90, 120, {0, BRIGHTNESS, BRIGHTNESS }) ;
Rain r4(90, 120, {0, BRIGHTNESS, BRIGHTNESS }) ;

//Glow glow(0, 50, RGB{0, 0, 10});
//Glow glow2(50, 100, RGB{10, 0, 10});

Duo m(0);

void setup() {
  //Serial.begin(9600);
  list = new AnimList(NUMLEDS);  
  //list->AddFirst(&glow);
  //list->Add(&glow2);
  list->AddFirst(&m);
  //list->AddFirst(&s);
  //list->Add(&m1);
  //list->Add(&m2);
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
