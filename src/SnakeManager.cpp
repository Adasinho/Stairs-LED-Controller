#include "SnakeManager.h"

SnakeManager::SnakeManager(Adafruit_NeoPixel *pixels, int color, Iterators *animationIterators) {
    this->pixels = pixels;
    this->color = color;
    this->busy = false;
    this->animationIterators = animationIterators;
}

SnakeManager::~SnakeManager() { 
    clear();
}

void SnakeManager::update() {
    bool workingSnakes = false;

    for(auto snake : snakes) {
        //int frontIterator = animationIterators->a != 0
        bool endAnimation = snake->update(pixels, color, animationIterators);
        if(endAnimation) remove(snake);
        else workingSnakes = true;
    }

    busy = workingSnakes;
}

void SnakeManager::clear() {
    for(auto snake : snakes) delete snake;
    snakes.clear();
}

void SnakeManager::add(AnimationDirection direction, int iteratorA, int iteratorB) {
    int numPixels = pixels->numPixels();
    Snake *snake = new Snake(numPixels, direction, iteratorA, iteratorB);
    snakes.push_back(snake);
}

void SnakeManager::remove(Snake *snakeToDelete) {
    snakes.erase(std::remove(snakes.begin(), snakes.end(), snakeToDelete), snakes.end());
}