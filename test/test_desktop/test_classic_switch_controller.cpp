#include <unity.h>
#include "ClassicSwitchController.h"

struct InputProps {
    bool stateA;
    bool stateB;
};

void testGenerator(InputProps *input, ControllerState expectedOutput, ControllerState startState, int size) {
    ClassicSwitchController *controller = new ClassicSwitchController();
    if(startState == ACTIVE_STATE) controller->update(true, false);
    controller->setState(startState);
    
    //int numberOfCases = sizeof(input) / sizeof(*input);
    int numberOfCases = size;

    for(int i = 0; i < numberOfCases; i++)
        controller->update(input[i].stateA, input[i].stateB);

    const ControllerState actual = controller->getState();
    const ControllerState expected = expectedOutput;

    TEST_ASSERT_EQUAL(expected, actual);

    delete controller;
}

void givenUpdateWhenBothStatesAreFalseThenSetIdleState(void) {
    InputProps input[] = {{false, false}};
    ControllerState expected = IDLE_STATE;

    testGenerator(input, expected, IDLE_STATE, 1);
}

void givenUpdateWhenFirstIsTrueAndSecoundIsFalseThenSetTriggeredAState(void) {
    InputProps input[] = {{true, false}};
    ControllerState expected = TRIGGERED_A_STATE;

    testGenerator(input, expected, IDLE_STATE, 1);
}

void givenUpdateWhenFirstIsFalseAndSecoundIsTrueThenSetTriggeredBState(void) {
    InputProps input[] = {{false, true}};
    ControllerState expected = TRIGGERED_B_STATE;

    testGenerator(input, expected, IDLE_STATE, 1);
}

void givenUpdateWhenBothStatesAreTrueThenSetIdleState(void) {
    InputProps input[] = {{true, true}};
    ControllerState expected = IDLE_STATE;

    testGenerator(input, expected, IDLE_STATE, 1);
}

//////////////////////////////////

void givenUpdateWhenBothStatesAreTrueAndWasTriggeredAThenSetFreedAState(void) { // add new animation
    InputProps input[] = {{true, false}, {true, true}};
    ControllerState expected = FREED_FROM_A_TO_B_STATE;

    testGenerator(input, expected, IDLE_STATE, 2);
}

void givenUpdateWhenBothStatesAreTrueAndWasTriggeredBThenSetFreedBState(void) { // add new animation
    InputProps input[] = {{false, true}, {true, true}};
    ControllerState expected = FREED_FROM_B_TO_A_STATE;

    testGenerator(input, expected, IDLE_STATE, 2);
}

void givenUpdateWhenBothStatesAreFalseAndWasTriggeredAThenSetFreedAState(void) {
    InputProps input[] = {{true, false}, {false, false}};
    ControllerState expected = FREED_A_STATE;

    testGenerator(input, expected, IDLE_STATE, 2);
}

void givenUpdateWhenBothStatesAreFalseAndWasTriggeredBThenSetFreedBState(void) {
    InputProps input[] = {{false, true}, {false, false}};
    ControllerState expected = FREED_B_STATE;

    testGenerator(input, expected, IDLE_STATE, 2);
}

//////////////////////////////////

void givenUpdateWhenFirstIsTrueAndSecoundIsFalseAndWasFreedAThenSetTriggeredAState(void) {
    InputProps input[] = {{true, false}, {false, false}, {true, false}};
    ControllerState expected = TRIGGERED_A_STATE;

    testGenerator(input, expected, IDLE_STATE, 3);
}

void givenUpdateWhenFirstIsFalseAndSecoundIsTrueAndWasFreedAThenSetTriggeredBState(void) { // add new animation
    InputProps input[] = {{true, false}, {false, false}, {false, true}};
    ControllerState expected = TRIGGERED_FROM_B_TO_A_STATE;

    testGenerator(input, expected, IDLE_STATE, 3);
}

void givenUpdateWhenFirstIsFalseAndSecoundIsTrueAndWasFreedBThenSetTriggeredBState(void) {
    InputProps input[] = {{false, true}, {false, false}, {false, true}};
    ControllerState expected = TRIGGERED_B_STATE;

    testGenerator(input, expected, IDLE_STATE, 3);
}

void givenUpdateWhenFirstIsTrueAndSecoundIsFalseAndWasFreedBThenSetTriggeredAState(void) { // add new animation
    InputProps input[] = {{false, true}, {false, false}, {true, false}};
    ControllerState expected = TRIGGERED_FROM_A_TO_B_STATE;

    testGenerator(input, expected, IDLE_STATE, 3);
}

//////////////////////////////////

void givenUpdateWhenBothAreFalseAndWasActiveThenSetFreedAState(void) {
    InputProps input[] = {{false, false}};
    ControllerState expected = FREED_A_STATE;

    testGenerator(input, expected, ACTIVE_STATE, 1);
}

void givenUpdateWhenBothAreTrueAndWasActiveThenSetFreedBState(void) {
    InputProps input[] = {{true, true}};
    ControllerState expected = FREED_B_STATE;

    testGenerator(input, expected, ACTIVE_STATE, 1);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(givenUpdateWhenBothStatesAreFalseThenSetIdleState);
    RUN_TEST(givenUpdateWhenFirstIsTrueAndSecoundIsFalseThenSetTriggeredAState);
    RUN_TEST(givenUpdateWhenFirstIsFalseAndSecoundIsTrueThenSetTriggeredBState);
    RUN_TEST(givenUpdateWhenBothStatesAreTrueThenSetIdleState);

    RUN_TEST(givenUpdateWhenBothStatesAreTrueAndWasTriggeredAThenSetFreedAState);
    RUN_TEST(givenUpdateWhenBothStatesAreTrueAndWasTriggeredBThenSetFreedBState);
    RUN_TEST(givenUpdateWhenBothStatesAreFalseAndWasTriggeredAThenSetFreedAState);
    RUN_TEST(givenUpdateWhenBothStatesAreFalseAndWasTriggeredBThenSetFreedBState);

    RUN_TEST(givenUpdateWhenFirstIsTrueAndSecoundIsFalseAndWasFreedAThenSetTriggeredAState);
    RUN_TEST(givenUpdateWhenFirstIsFalseAndSecoundIsTrueAndWasFreedAThenSetTriggeredBState);
    RUN_TEST(givenUpdateWhenFirstIsFalseAndSecoundIsTrueAndWasFreedBThenSetTriggeredBState);
    RUN_TEST(givenUpdateWhenFirstIsTrueAndSecoundIsFalseAndWasFreedBThenSetTriggeredAState);

    RUN_TEST(givenUpdateWhenBothAreFalseAndWasActiveThenSetFreedAState);
    RUN_TEST(givenUpdateWhenBothAreTrueAndWasActiveThenSetFreedBState);
    UNITY_END();

    return 0;
}