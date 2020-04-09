//
// Created by adirm on 06.04.2020.
//

#include "Animation.h"

Animation::Animation(Adafruit_NeoPixel *pixels) {
    this->numPixels = pixels->numPixels();
    this->iteratorA = 0;
    this->iteratorB = numPixels - 1;
    this->pixels = pixels;
}

bool Animation::introFromAToBFrame(uint8_t color) {
    this->pixels->setPixelColor(iteratorA, this->pixels->Color(color, color, color));
    this->pixels->show();

    if(iteratorA < iteratorB) {
        iteratorA++;
        return false;
    } else {
        iteratorA = numPixels - 1;
        iteratorB = 0;
        return true;
    }
}

bool Animation::outroFromBToAFrame() {
    this->pixels->setPixelColor(iteratorA, this->pixels->Color(0, 0, 0));
    this->pixels->show();

    if(iteratorA - 1 >= 0) {
        iteratorA--;
        iteratorB = this->numPixels - 1; // fix for improve speed
        return false;
    } else {
        iteratorA = 0;
        return true;
    }
}

bool Animation::introFromBToAFrame(uint8_t color) {
    this->pixels->setPixelColor(iteratorB, this->pixels->Color(color, color, color));
    this->pixels->show();

    if(iteratorB > iteratorA) {
        iteratorB--;
        return false;
    } else {
        iteratorA = this->numPixels - 1;
        iteratorB = 0;
        return true;
    }
}

bool Animation::outroFromAToBFrame() {
    this->pixels->setPixelColor(iteratorB, this->pixels->Color(0, 0, 0));
    this->pixels->show();

    if(iteratorB - 1 < numPixels) {
        iteratorA = 0; // fix for improve speed
        iteratorB++;
        return false;
    } else {
        iteratorB = numPixels - 1;
        return true;
    }
}

bool Animation::introBetweenFrame(uint8_t color) {
    this->pixels->setPixelColor(iteratorA, this->pixels->Color(color, color, color));
    this->pixels->setPixelColor(iteratorB, this->pixels->Color(color, color, color));
    this->pixels->show();

    if(iteratorA < iteratorB) {
        iteratorA++;
        iteratorB--;
        return false;
    } else {
        iteratorA = numPixels - 1;
        iteratorB = 0;
        return true;
    }
}

void Animation::resetIteratorA() {
    iteratorA = 0;
}

void Animation::resetIteratorB() {
    iteratorB = numPixels - 1;
}