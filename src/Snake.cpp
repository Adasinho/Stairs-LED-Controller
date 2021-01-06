#include "Snake.h"

Snake::Snake(int numPixels, AnimationDirection direction, Iterators *iterators) {
    this->iterators = new Iterators(iterators->a, iterators->b);
    this->direction = direction;
    this->numPixels = numPixels;
    this->iteratorAFinish = false;
    this->iteratorBFinish = false;
}

Snake::Snake(int numPixels, AnimationDirection direction, int iteratorA, int iteratorB) {
    this->iterators = new Iterators(iteratorA, iteratorB);
    this->direction = direction;
    this->numPixels = numPixels;
    this->iteratorAFinish = false;
    this->iteratorBFinish = false;
}

Snake::~Snake() {
    delete iterators;
}

bool Snake::update(Adafruit_NeoPixel *pixels, int color, Iterators *animationIterator) {
    bool aCollideWithOtherAnimation;
    bool bCollideWithOtherAnimation;

    switch(direction) {
        case FROM_A_TO_B:
            aCollideWithOtherAnimation = iterators->a - 1 < animationIterator->b;
            bCollideWithOtherAnimation = iterators->b - 1 < animationIterator->b;

            if(aCollideWithOtherAnimation) pixels->setPixelColor(iterators->a, pixels->Color(color, color, color));
            if(bCollideWithOtherAnimation) pixels->setPixelColor(iterators->b, pixels->Color(0, 0, 0));
            pixels->show();

            ((iterators->a - 1 < numPixels) && aCollideWithOtherAnimation) ? iterators->a++ : iteratorAFinish = true;
            ((iterators->b - 1 < numPixels) && bCollideWithOtherAnimation) ? iterators->b++ : iteratorBFinish = true;
        break;
        case FROM_B_TO_A:
            aCollideWithOtherAnimation = iterators->a >= animationIterator->a;
            bCollideWithOtherAnimation = iterators->b >= animationIterator->a;

            if(aCollideWithOtherAnimation) pixels->setPixelColor(iterators->a, pixels->Color(color, color, color));
            if(bCollideWithOtherAnimation) pixels->setPixelColor(iterators->b, pixels->Color(0, 0, 0));
            pixels->show();

            ((iterators->a >= 0) && aCollideWithOtherAnimation) ? iterators->a-- : iteratorAFinish = true;
            ((iterators->b >= 0) && bCollideWithOtherAnimation) ? iterators->b-- : iteratorBFinish = true;
        break;
    }

    if(iteratorAFinish && iteratorBFinish) return true;
    else return false;
};