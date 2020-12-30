//
// Created by adirm on 06.04.2020.
//

#ifndef ESP8266_STAIR_WORKPLACE_ANIMATION_H
#define ESP8266_STAIR_WORKPLACE_ANIMATION_H

#include "Adafruit_NeoPixel.h"

class Animation {
public:
    Animation(Adafruit_NeoPixel *pixels);
    bool fromToNextFrame(uint8_t color);
    bool toFromNextFrame(uint8_t color);
    bool introFromAToBFrame(uint8_t color);
    bool introFromBToAFrame(uint8_t color);
    bool introBetweenFrame(uint8_t color);
    bool outroFromAToBFrame();
    bool outroFromBToAFrame();
    bool outro();
    void resetIteratorA();
    void resetIteratorB();

private:
    int numPixels;
    int iteratorA, iteratorB;
    Adafruit_NeoPixel *pixels;
};


#endif //ESP8266_STAIR_WORKPLACE_ANIMATION_H
