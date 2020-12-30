#include "TacticSwitchController.h"

TacticSwitchController::TacticSwitchController(uint8_t startPinNumber, uint8_t endPinNumber) : Control(startPinNumber, endPinNumber) {
    switchA = new TacticSwitch();
    switchB = new TacticSwitch();
}

TacticSwitchController::~TacticSwitchController() {
    delete switchA;
    delete switchB;
}

void TacticSwitchController::update() {
    bool switchAValue = startPin->getValue();
    bool switchBValue = endPin->getValue();

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