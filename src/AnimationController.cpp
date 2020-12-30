#include "AnimationController.h"
#include "MotionSensorController.h"
#include "TacticSwitchController.h"
#include "ClassicSwitchController.h"

template <typename ControlerType>
AnimationController<ControlerType>::AnimationController(int numPixels, int ledStripPin, int sensorAPin, int sensorBPin, int delayValue) {
    this->pixels = new Adafruit_NeoPixel(numPixels, ledStripPin, NEO_GRB + NEO_KHZ800);
    this->animation = new Animation(this->pixels);
    this->controller = new ControlerType(sensorAPin, sensorBPin);
    this->delayValue = delayValue;
    this->lastTime = millis();

    this->pixels->begin();
}

template <typename ControlerType>
void AnimationController<ControlerType>::update() {
    controller->update();

    ControllerState sensorState = controller->getState();

    if(checkTime()) {
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
            case ACTIVE_STATE:

            break;
            case FREED_A_STATE:
                if(animation->outroFromBToAFrame()) controller->setState(IDLE_STATE);
            break;
            case FREED_B_STATE:
                if(animation->outroFromAToBFrame()) controller->setState(IDLE_STATE);
            break;
            case FREED_STATE:
                if(animation->outro()) controller->setState(IDLE_STATE);
            case IDLE_STATE:

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