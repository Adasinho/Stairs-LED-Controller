#ifndef SNAKE_MANAGER
#define SNAKE_MANAGER

#include "Snake.h"

class SnakeManager {
    public:
    SnakeManager(Adafruit_NeoPixel *pixels, int color, Iterators *animationIterators);
    ~SnakeManager();
    void update();
    void clear();
    void add(AnimationDirection direction, int iteratorA, int iteratorB);
    void remove(Snake *snake);
    bool isBusy() { return busy; }

    private:
    Adafruit_NeoPixel *pixels;
    std::vector<Snake*> snakes;
    Iterators *animationIterators;
    int color;
    bool busy;
};

#endif // SNAKE_MANAGER