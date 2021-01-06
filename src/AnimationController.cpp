#include "AnimationController.h"
#include "MotionSensorController.h"
#include "TacticSwitchController.h"
#include "ClassicSwitchController.h"

template <typename ControlerType>
AnimationController<ControlerType>::AnimationController(int numPixels, int ledStripPin, int sensorAPin, int sensorBPin, int delayValue) {
    this->pixels = new Adafruit_NeoPixel(numPixels, ledStripPin, NEO_GRB + NEO_KHZ800);
    this->animation = new Animation(this->pixels);
    this->controller = new ControlerType();
    this->delayValue = delayValue;
    this->lastTime = millis();
    this->startPin = new GPIOHelper(sensorAPin, INPUT);
    this->endPin = new GPIOHelper(sensorBPin, INPUT);

    this->pixels->begin();
    this->pixels->setBrightness(64);
}

template <typename ControlerType>
void AnimationController<ControlerType>::update() {
    controller->update(startPin->getValue(), endPin->getValue());

    if(checkTime()) {
        ControllerState sensorState = controller->getState();

        switch(sensorState) {
            case TRIGGERED_A_STATE:
                if(animation->introFromAToBFrame(255)) controller->setState(ACTIVE_STATE);
            break;
            case TRIGGERED_B_STATE:
                if(animation->introFromBToAFrame(255)) controller->setState(ACTIVE_STATE);
            break;
            case TRIGGERED_STATE:
                if(animation->introBetweenFrame(255)) controller->setState(ACTIVE_STATE);
            break;
            case TRIGGERED_FROM_A_TO_B_STATE:
                if(animation->introSnakeFromAToBFrame(255)) controller->setState(ACTIVE_STATE);
            break;
            case TRIGGERED_FROM_B_TO_A_STATE:
                if(animation->introSnakeFromBToAFrame(255)) controller->setState(ACTIVE_STATE);
            break;
            case ACTIVE_STATE:
                animation->activeFrame();
            break;
            case FREED_A_STATE:
                if(animation->outroFromBToAFrame()) controller->setState(IDLE_STATE);
            break;
            case FREED_B_STATE:
                if(animation->outroFromAToBFrame()) controller->setState(IDLE_STATE);
            break;
            case FREED_FROM_A_TO_B_STATE:
                if(animation->outroSnakeFromAToBFrame(255)) controller->setState(IDLE_STATE);
            break;
            case FREED_FROM_B_TO_A_STATE:
                if(animation->outroSnakeFromBToAFrame(255)) controller->setState(IDLE_STATE);
            break;
            case FREED_STATE:
                if(animation->outro()) controller->setState(IDLE_STATE);
            break;
            case IDLE_STATE:
                animation->idleFrame();
            break;
        }
    }

    controller->updateStates();
}

template <typename ControlerType>
void AnimationController<ControlerType>::triggeredAnimation() {
    switch(controller->checkFromStartToEndDirection()) {
        case true:
            if(this->animation->fromToNextFrame(255))
                this->controller->setState(ACTIVE_STATE);
        break;
        case false:
            if(this->animation->toFromNextFrame(255))
                this->controller->setState(ACTIVE_STATE);
    }
}

template <typename ControlerType>
void AnimationController<ControlerType>::freedAnimation() {

}

template <typename ControlerType>
bool AnimationController<ControlerType>::checkTime() {
    unsigned long actualTime = millis();

    if(actualTime > lastTime + delayValue) {
        lastTime = actualTime;
        return true;
    } else return false;
}

template class AnimationController<MotionSensorController>;
template class AnimationController<TacticSwitchController>;
template class AnimationController<ClassicSwitchController>;