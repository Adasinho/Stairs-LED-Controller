//
// Created by adirm on 06.04.2020.
//

#include "Animation.h"
#include "Helpers.h"
#include <vector>

Animation::Animation(Adafruit_NeoPixel *pixels) {
    this->numPixels = pixels->numPixels();
    this->pixels = pixels;
    this->iteratorsInMove = false;
    this->iterators = new Iterators(0, numPixels - 1);
    this->snakeManager = new SnakeManager(pixels, 255, iterators);
}

Animation::~Animation() {
    delete snakeManager;
}

bool Animation::introFromAToBFrame(uint8_t color) {
    updateState(TRIGGERED_A_STATE);

    this->pixels->setPixelColor(iterators->a, this->pixels->Color(color, color, color));
    this->pixels->show();

    if(iterators->a < iterators->b) {
        iterators->a++;
        return false;
    } else {
        iterators->a = numPixels - 1;
        iterators->b = 0;
        return true;
    }
}

bool Animation::outroFromBToAFrame() {
    updateState(FREED_A_STATE);

    this->pixels->setPixelColor(iterators->a, this->pixels->Color(0, 0, 0));
    this->pixels->show();

    if(iterators->a - 1 >= 0) {
        iterators->a--;
        iterators->b = this->numPixels - 1; // fix for improve speed
        return false;
    } else {
        iterators->a = 0;
        return true;
    }
}

bool Animation::introFromBToAFrame(uint8_t color) {
    updateState(TRIGGERED_B_STATE);

    this->pixels->setPixelColor(iterators->b, this->pixels->Color(color, color, color));
    this->pixels->show();

    if(iterators->b > iterators->a) {
        iterators->b--;
        return false;
    } else {
        iterators->a = numPixels - 1;
        iterators->b = 0;
        return true;
    }
}

bool Animation::outroFromAToBFrame() {
    updateState(FREED_B_STATE);

    this->pixels->setPixelColor(iterators->b, this->pixels->Color(0, 0, 0));
    this->pixels->show();

    if(iterators->b - 1 < numPixels) {
        iterators->a = 0; // fix for improve speed
        iterators->b++;
        return false;
    } else {
        iterators->b = numPixels - 1;
        return true;
    }
}

bool Animation::outro() {
    updateState(FREED_STATE);

    this->pixels->setPixelColor(iterators->a, this->pixels->Color(0, 0, 0));
    this->pixels->setPixelColor(iterators->b, this->pixels->Color(0, 0, 0));
    this->pixels->show();

    bool iteratorAFinish = false;
    bool iteratorBFinish = false;

    if(iterators->b - 1 < numPixels) {
        //iteratorA = 0; // fix for improve speed
        iterators->b++;
    } else {
        iterators->b = numPixels - 1;
        iteratorBFinish = true;
    }

    if(iterators->a - 1 >= 0) {
        iterators->a--;
        //iteratorB = this->numPixels - 1; // fix for improve speed
    } else {
        iterators->a = 0;
        iteratorAFinish = true;
    }

    return iteratorAFinish && iteratorBFinish;
}

bool Animation::introBetweenFrame(uint8_t color) {
    updateState(TRIGGERED_STATE);

    this->pixels->setPixelColor(iterators->a, this->pixels->Color(color, color, color));
    this->pixels->setPixelColor(iterators->b, this->pixels->Color(color, color, color));
    this->pixels->show();

    if(!iteratorsInMove) {
        if(iterators->a < iterators->b) {
            iterators->a++;
            iterators->b--;
            return false;
        } else {
            iterators->a = numPixels - 1;
            iterators->b = 0;
            return true;
        }
    } else {

    }
}

bool Animation::introSnakeFromAToBFrame(uint8_t color) {
    updateState(TRIGGERED_FROM_A_TO_B_STATE);

    this->pixels->setPixelColor(iterators->b, this->pixels->Color(0, 0, 0));
    this->pixels->setPixelColor(iterators->a, this->pixels->Color(color, color, color));
    this->pixels->show();

    bool iteratorAFinish = false;
    bool iteratorBFinish = false;

    (iterators->a - 1 < numPixels) ? iterators->a++ : iteratorAFinish = true;
    (iterators->b - 1 < numPixels) ? iterators->b++ : iteratorBFinish = true;

    if(iteratorAFinish && iteratorBFinish) {
        iterators->a = numPixels - 1;
        iterators->b = 0;
        return true;
    } else return false;
}

bool Animation::introSnakeFromBToAFrame(uint8_t color) {
    updateState(TRIGGERED_FROM_B_TO_A_STATE);

    this->pixels->setPixelColor(iterators->a, this->pixels->Color(0, 0, 0));
    this->pixels->setPixelColor(iterators->b, this->pixels->Color(color, color, color));
    this->pixels->show();

    bool iteratorAFinish = false;
    bool iteratorBFinish = false;

    (iterators->a - 1 >= 0) ? iterators->a-- : iteratorAFinish = true;
    (iterators->b - 1 >= 0) ? iterators->b-- : iteratorBFinish = true;
    
    if(iteratorAFinish && iteratorBFinish) {
        iterators->a = numPixels - 1;
        iterators->b = 0;
        return true;
    } else return false;
}

bool Animation::outroSnakeFromAToBFrame(uint8_t color) {
    updateState(FREED_FROM_A_TO_B_STATE);
  
    //this->pixels->setPixelColor(iteratorA, this->pixels->Color(color, color, color));
    this->pixels->setPixelColor(iterators->b, this->pixels->Color(0, 0, 0));
    this->pixels->show();

    //bool iteratorAFinish = false;
    bool iteratorBFinish = false;

    //(iteratorA - 1 < numPixels) ? iteratorA++ : iteratorAFinish = true;
    (iterators->b - 1 < numPixels) ? iterators->b++ : iteratorBFinish = true;

    if(!snakeManager->isBusy() && iteratorBFinish) {
        iterators->a = 0;
        iterators->b = numPixels - 1;
        return true;
    } else return false;
}

bool Animation::outroSnakeFromBToAFrame(uint8_t color) {
    updateState(FREED_FROM_B_TO_A_STATE);

    //this->pixels->setPixelColor(iteratorB, this->pixels->Color(color, color, color));
    this->pixels->setPixelColor(iterators->a, this->pixels->Color(0, 0, 0));
    this->pixels->show();

    bool iteratorAFinish = false;
    //bool iteratorBFinish = false;

    (iterators->a - 1 >= 0) ? iterators->a-- : iteratorAFinish = true;
    //(iteratorB - 1 >= 0) ? iteratorB-- : iteratorBFinish = true;

    if(!snakeManager->isBusy() && iteratorAFinish) {
        iterators->a = 0;
        iterators->b = numPixels - 1;
        return true;
    } else return false;
}

void Animation::idleFrame() {
    updateState(IDLE_STATE);
}

void Animation::activeFrame() {
    updateState(ACTIVE_STATE);
}

void Animation::updateState(ControllerState actualState) {
    if(state != actualState) {
        String printedValue = "New state: " + getStateStringName(actualState);
        Serial.println(printedValue);
        
        if((state == TRIGGERED_A_STATE) || (state == TRIGGERED_FROM_A_TO_B_STATE)) {
            if(actualState == FREED_FROM_A_TO_B_STATE) {
                //iterators->b = 0;
                snakeManager->add(FROM_A_TO_B, iterators->a, 0);
            }
        }

        if((state == TRIGGERED_B_STATE) || (state == TRIGGERED_FROM_B_TO_A_STATE)) {
            if(actualState == FREED_FROM_B_TO_A_STATE) {
                //iterators->a = numPixels - 1;
                snakeManager->add(FROM_B_TO_A, iterators->b, numPixels -1);
            }
        }

        if(state == FREED_FROM_A_TO_B_STATE || state == FREED_FROM_B_TO_A_STATE) {
            iterators->a = 0;
            iterators->b = numPixels - 1;

            if(actualState == TRIGGERED_STATE) {
                iteratorsInMove = true;
                //return;
            }
        }

        if(state == FREED_A_STATE) {
            if(actualState == TRIGGERED_FROM_B_TO_A_STATE) {
                Serial.println(iterators->a);
                Serial.println(iterators->b);

                iterators->b = numPixels - 1;
            }
        }

        state = actualState;
    }

    snakeManager->update();
}

void Animation::resetIteratorA() {
    iterators->a = 0;
}

void Animation::resetIteratorB() {
    iterators->b = numPixels - 1;
}