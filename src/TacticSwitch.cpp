#include "TacticSwitch.h"

TacticSwitch::TacticSwitch() {
    int activeDuration = 5000;
    timer = new Timer(activeDuration);
}

TacticSwitch::~TacticSwitch() {
    delete timer;
}

void TacticSwitch::update(bool switchState) {
    if(switchState) {
        timer->setTimer();
    }

    timer->update();
    bool timerIsBusy = timer->isBusy();

    StateController::update(timerIsBusy);
}