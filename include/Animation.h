//
// Created by adirm on 06.04.2020.
//

#ifndef ESP8266_STAIR_WORKPLACE_ANIMATION_H
#define ESP8266_STAIR_WORKPLACE_ANIMATION_H

#include "Adafruit_NeoPixel.h"
#include "Collections.h"

class Animation {
public:
    Animation(Adafruit_NeoPixel *pixels);
    bool fromToNextFrame(uint8_t color);
    bool toFromNextFrame(uint8_t color);
    bool introFromAToBFrame(uint8_t color);
    bool introFromBToAFrame(uint8_t color);
    bool introSnakeFromAToBFrame(uint8_t color);
    bool introSnakeFromBToAFrame(uint8_t color);
    bool introBetweenFrame(uint8_t color);
    bool outroFromAToBFrame();
    bool outroFromBToAFrame();
    bool outroSnakeFromAToBFrame(uint8_t color);
    bool outroSnakeFromBToAFrame(uint8_t color);
    bool outro();
    void idleFrame();
    void activeFrame();
    void resetIteratorA();
    void resetIteratorB();

private:
    void updateState(ControllerState actualState);

    int numPixels;
    int iteratorA, iteratorB;
    bool iteratorsInMove;
    ControllerState state;
    Adafruit_NeoPixel *pixels;
};


#endif //ESP8266_STAIR_WORKPLACE_ANIMATION_H
