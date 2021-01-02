#include "TacticSwitchController.h"

TacticSwitchController::TacticSwitchController() : Control() {
    switchA = new TacticSwitch();
    switchB = new TacticSwitch();
}

TacticSwitchController::~TacticSwitchController() {
    delete switchA;
    delete switchB;
}

void TacticSwitchController::update(bool stateA, bool stateB) {
    bool switchAValue = stateA;
    bool switchBValue = stateB;

    ControllerState lastState = state;

    switchA->update(switchAValue);
    switchB->update(switchBValue);

    bool switchATriggered = switchA->checkIfTriggered();
    bool switchBTriggered = switchB->checkIfTriggered();

    checkIfControllerTriggered(switchATriggered, switchBTriggered);

    bool switchAFreed = switchA->checkIfFreed();
    bool switchBFreed = switchB->checkIfFreed();

    checkIfControllerFreed(switchAFreed, switchBFreed);

    if(lastState != state) stateChanged = true;
}