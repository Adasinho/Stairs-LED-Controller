#include "AnimationController.h"

AnimationController::AnimationController(int numPixels, int ledStripPin, int sensorAPin, int sensorBPin, int delayValue) {
    this->pixels = new Adafruit_NeoPixel(numPixels, ledStripPin, NEO_GRB + NEO_KHZ800);
    this->animation = new Animation(this->pixels);
    this->motionSensorController = new MotionSensorController(sensorAPin, sensorBPin);
    this->delayValue = delayValue;
    this->lastTime = millis();

    this->pixels->begin();
}

void AnimationController::update() {
    motionSensorController->update();

    SensorState sensorState = motionSensorController->getState();

    /*
    if(motionSensorController->checkIfStateChanged()) {
        switch(sensorState) {
            case triggeredAState:
                animation->resetIteratorB();
                break;
            case triggeredBState:
                animation->resetIteratorA();
                break;

        }
    }
    */

    if(checkTime()) {
        switch(sensorState) {
            case triggeredAState:
                if(animation->introFromAToBFrame(255)) motionSensorController->setState(activeState);
            break;
            case triggeredBState:
                if(animation->introFromBToAFrame(255)) motionSensorController->setState(activeState);
            break;
            case triggeredState:
                if(animation->introBetweenFrame(255)) motionSensorController->setState(activeState);
            break;
            case activeState:

            break;
            case freedAState:
                if(animation->outroFromBToAFrame()) motionSensorController->setState(idleState);
            break;
            case freedBState:
                if(animation->outroFromAToBFrame()) motionSensorController->setState(idleState);
            break;

            case idleState:

            break;
        }
    }

    motionSensorController->updateStates();
}

void AnimationController::triggeredAnimation() {
    switch(motionSensorController->checkFromStartToEndDirection()) {
        case true:
            if(this->animation->fromToNextFrame(255))
                this->motionSensorController->setState(activeState);
        break;
        case false:
            if(this->animation->toFromNextFrame(255))
                this->motionSensorController->setState(activeState);
    }
}

void AnimationController::freedAnimation() {

}

bool AnimationController::checkTime() {
    unsigned long actualTime = millis();

    if(actualTime > lastTime + delayValue) {
        lastTime = actualTime;
        return true;
    } else return false;
}