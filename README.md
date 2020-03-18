# ledstripanimator
An animation library for the arduino WS212 LED strips

This project is intended to control any WS2812 RGB ledstrip with any number of LED's. 

It contains two library classes.

1. Animation
2. AnimList

Animation has two pure virtual functions.

bool UpdateFrame(Adafruit_NeoPixel &strip);
void Render(Adafruit_NeoPixel &strip);

With UpdateFrame you can update the positional variables of which leds to light up.
It has a boolean return value to indicate if the Animation is done and must be removed from the animation list.

With Render the actual leds' are lighted. It has no return value.

AnimList is a linked list of Animation classes and holds a reference to an adafruit neopixel led strip.
Initialize it with the number of leds on the strip in arduino's setup function.

```C++
#define NUMLEDS 144

void setup() {
  list = new AnimList(NUMLEDS);  
}
```

Then in arduino's main loop function, call UpdateFrame and Render as fast as possible.

```C++
void loop() {   
  list->UpdateFrame();
  list->Render();
}
```

This is the structure of the animation list, right now it's up and running but it doesnt do anything yet.
Concrete animations must be added to the list.
Let's go with a simple example where one led lights up white and moves through the strip.

Here's the full class, let's break it down after.

```C++
class Move : public Animation
{
  unsigned char cur;
public:
  Move() : cur(0) { ms = 500; }

  bool UpdateFrame(Adafruit_NeoPixel &strip)
  {    
    if (cur == NUMLEDS) return false;
    cur++;
    return true;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
  }

  void Render(Adafruit_NeoPixel &strip)
  {
    strip.setPixelColor(cur, strip.Color(10, 10, 10));
  }
};
```

First, we declare the Move class and let it inherit from Animation. Now it can be added to the AnimList.
We set the ms value to 500 which means that every 500 milliseconds UpdateFrame is called and the LED moves twice a second on the strip. This works because the arduino is a realtime operating system and 500 milliseconds is always 500 milliseconds.

Then override UpdateFrame and Render. You have to do this as they are pure virtuals, otherwise the code does not compile.

The Move class has one variable, an unsigned char 'cur' that can have up to 256 positions.
It represents the current position of the LED to light up. Zero is the first led and NUMLEDS is the last.
Then in UpdateFrame we just increment the cur variable so it moves up one position in the led strip.
We check if cur has reached the LED and if it has then we remove it from the animation list by returning false.
The AnimList takes care of that.

In Render we call only Adafruit's neopixel library function setPixelColor and pass it the current variable and an RGB value of RGB(10,10,10)

This is white. Do not use the maximum RGB(255, 255, 255) as this takes way too much energy, the leds will cannot handle that.

So now we have a strip where one led ligts up and it moves twice a second on the ledstrip.
After it reaches the last LED it does nothiong anymore.
