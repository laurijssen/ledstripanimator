#ifndef ANIMLIST_H
#define ANIMLIST_H

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

#endif
