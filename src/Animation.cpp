//
// Created by adirm on 06.04.2020.
//

#include "Animation.h"
#include "Helpers.h"

Animation::Animation(Adafruit_NeoPixel *pixels) {
    this->numPixels = pixels->numPixels();
    this->iteratorA = 0;
    this->iteratorB = numPixels - 1;
    this->pixels = pixels;
    this->iteratorsInMove = false;
}

bool Animation::introFromAToBFrame(uint8_t color) {
    updateState(TRIGGERED_A_STATE);

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
    updateState(FREED_A_STATE);

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
    updateState(TRIGGERED_B_STATE);

    this->pixels->setPixelColor(iteratorB, this->pixels->Color(color, color, color));
    this->pixels->show();

    if(iteratorB > iteratorA) {
        iteratorB--;
        return false;
    } else {
        iteratorA = numPixels - 1;
        iteratorB = 0;
        return true;
    }
}

bool Animation::outroFromAToBFrame() {
    updateState(FREED_B_STATE);

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

bool Animation::outro() {
    updateState(FREED_STATE);

    this->pixels->setPixelColor(iteratorA, this->pixels->Color(0, 0, 0));
    this->pixels->setPixelColor(iteratorB, this->pixels->Color(0, 0, 0));
    this->pixels->show();

    bool iteratorAFinish = false;
    bool iteratorBFinish = false;

    if(iteratorB - 1 < numPixels) {
        //iteratorA = 0; // fix for improve speed
        iteratorB++;
    } else {
        iteratorB = numPixels - 1;
        iteratorBFinish = true;
    }

    if(iteratorA - 1 >= 0) {
        iteratorA--;
        //iteratorB = this->numPixels - 1; // fix for improve speed
    } else {
        iteratorA = 0;
        iteratorAFinish = true;
    }

    return iteratorAFinish && iteratorBFinish;
}

bool Animation::introBetweenFrame(uint8_t color) {
    updateState(TRIGGERED_STATE);

    this->pixels->setPixelColor(iteratorA, this->pixels->Color(color, color, color));
    this->pixels->setPixelColor(iteratorB, this->pixels->Color(color, color, color));
    this->pixels->show();

    if(!iteratorsInMove) {
        if(iteratorA < iteratorB) {
            iteratorA++;
            iteratorB--;
            return false;
        } else {
            iteratorA = numPixels - 1;
            iteratorB = 0;
            return true;
        }
    } else {

    }
}

bool Animation::introSnakeFromAToBFrame(uint8_t color) {
    updateState(TRIGGERED_FROM_A_TO_B_STATE);

    this->pixels->setPixelColor(iteratorB, this->pixels->Color(0, 0, 0));
    this->pixels->setPixelColor(iteratorA, this->pixels->Color(color, color, color));
    this->pixels->show();

    bool iteratorAFinish = false;
    bool iteratorBFinish = false;

    (iteratorA - 1 < numPixels) ? iteratorA++ : iteratorAFinish = true;
    (iteratorB - 1 < numPixels) ? iteratorB++ : iteratorBFinish = true;

    if(iteratorAFinish && iteratorBFinish) {
        iteratorA = numPixels - 1;
        iteratorB = 0;
        return true;
    } else return false;
}

bool Animation::introSnakeFromBToAFrame(uint8_t color) {
    updateState(TRIGGERED_FROM_B_TO_A_STATE);

    this->pixels->setPixelColor(iteratorA, this->pixels->Color(0, 0, 0));
    this->pixels->setPixelColor(iteratorB, this->pixels->Color(color, color, color));
    this->pixels->show();

    bool iteratorAFinish = false;
    bool iteratorBFinish = false;

    (iteratorA - 1 >= 0) ? iteratorA-- : iteratorAFinish = true;
    (iteratorB - 1 >= 0) ? iteratorB-- : iteratorBFinish = true;
    
    if(iteratorAFinish && iteratorBFinish) {
        iteratorA = numPixels - 1;
        iteratorB = 0;
        return true;
    } else return false;
}

bool Animation::outroSnakeFromAToBFrame(uint8_t color) {
    updateState(FREED_FROM_A_TO_B_STATE);

    this->pixels->setPixelColor(iteratorA, this->pixels->Color(color, color, color));
    this->pixels->setPixelColor(iteratorB, this->pixels->Color(0, 0, 0));
    this->pixels->show();

    bool iteratorAFinish = false;
    bool iteratorBFinish = false;

    (iteratorA - 1 < numPixels) ? iteratorA++ : iteratorAFinish = true;
    (iteratorB - 1 < numPixels) ? iteratorB++ : iteratorBFinish = true;

    if(iteratorAFinish && iteratorBFinish) {
        iteratorA = 0;
        iteratorB = numPixels - 1;
        return true;
    } else return false;
}

bool Animation::outroSnakeFromBToAFrame(uint8_t color) {
    updateState(FREED_FROM_B_TO_A_STATE);

    this->pixels->setPixelColor(iteratorB, this->pixels->Color(color, color, color));
    this->pixels->setPixelColor(iteratorA, this->pixels->Color(0, 0, 0));
    this->pixels->show();

    bool iteratorAFinish = false;
    bool iteratorBFinish = false;

    (iteratorA - 1 >= 0) ? iteratorA-- : iteratorAFinish = true;
    (iteratorB - 1 >= 0) ? iteratorB-- : iteratorBFinish = true;

    if(iteratorAFinish && iteratorBFinish) {
        iteratorA = 0;
        iteratorB = numPixels - 1;
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
        
        if(state == TRIGGERED_A_STATE) {
            if(actualState == FREED_FROM_A_TO_B_STATE) {
                iteratorB = 0;
            }
        }

        if(state == TRIGGERED_B_STATE) {
            if(actualState == FREED_FROM_B_TO_A_STATE) {
                iteratorA = numPixels - 1;
            }
        }

        if(state == FREED_FROM_A_TO_B_STATE || state == FREED_FROM_B_TO_A_STATE) {
            if(actualState == TRIGGERED_STATE) {
                iteratorsInMove = true;
                //return;
            }
        }

        state = actualState;
    }
}

void Animation::resetIteratorA() {
    iteratorA = 0;
}

void Animation::resetIteratorB() {
    iteratorB = numPixels - 1;
}