#include "ClassicSwitchController.h"

ClassicSwitchController::ClassicSwitchController() : Control() {
    switchA = new StateController();
    switchB = new StateController();

    active = false;
    stateSwitchB = false;
    stateSwitchA = false;
}

ClassicSwitchController::~ClassicSwitchController() {
    delete switchA;
    delete switchB;
}

void ClassicSwitchController::update(bool stateA, bool stateB) {
    bool switchAValue = stateA;
    bool switchBValue = stateB;

    ControllerState lastState = state;

    switchA->update(switchAValue);
    switchB->update(switchBValue);
    
    bool switchAChanged = switchA->checkIfTriggered() || switchA->checkIfFreed();
    bool switchBChanged = switchB->checkIfTriggered() || switchB->checkIfFreed();

    if(switchAChanged) {
        stateSwitchA = !stateSwitchA;

        if(active) {
            freed = true;
            if(stateSwitchB) state = FREED_B_STATE;
            else if(lastState == ACTIVE_STATE) state = FREED_A_STATE;
            else state = FREED_STATE;
            active = false;
        } else {
            if(!triggered) {
                fromStartToEndAnimation = true;
                triggered = true;
                if(stateSwitchB) state = TRIGGERED_B_STATE;
                else state = TRIGGERED_A_STATE;
                active = true;
            }
        }
    }

    if(switchBChanged) {
        stateSwitchB = !stateSwitchB;

        if(active) {
            freed = true;
            if(stateSwitchA) state = FREED_A_STATE;
            else if(lastState == ACTIVE_STATE) state = FREED_B_STATE;
            else state = FREED_STATE;
            active = false;
        } else {
            if(!triggered) {
                fromStartToEndAnimation = false;
                triggered = true;
                if(stateSwitchA) state = TRIGGERED_A_STATE;
                else state = TRIGGERED_B_STATE;
                active = true;
            }
        }
    }

    if(lastState != state) stateChanged = true;
}