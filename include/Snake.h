#ifndef SNAKE
#define SNAKE

#include <Adafruit_NeoPixel.h>
#include "Collections.h"

struct Iterators {
    public:
    Iterators(int a, int b) {
        this->a = a;
        this->b = b;
    }

    int a;
    int b;
};

class Snake {
    public:
    Snake(int numPixels, AnimationDirection direction, Iterators *iterators);
    Snake(int numPixels, AnimationDirection direction, int iteratorA, int iteratorB);
    ~Snake();
    bool update(Adafruit_NeoPixel *pixels, int color, Iterators *animationIterator);

    private:
    AnimationDirection direction;
    Iterators *iterators;
    int numPixels;
    bool iteratorAFinish;
    bool iteratorBFinish;
};

#endif // SNAKE