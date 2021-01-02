#include <unity.h>
#include "ClassicSwitchController.h"

struct InputProps {
    bool stateA;
    bool stateB;
};

void testGenerator(InputProps *input, ControllerState *expectedOutput, ControllerState startState) {
    ClassicSwitchController *controller = new ClassicSwitchController();
    controller->setState(startState);
    int numberOfCases = sizeof(input) / sizeof(*input) - 1;

    for(int i = 0; i < numberOfCases; i++) {
        controller->update(input[i].stateA, input[i].stateB);
        controller->updateStates();

        const ControllerState actual = controller->getState();
        const ControllerState expected = expectedOutput[i];

        TEST_ASSERT_EQUAL(expected, actual);
    }

    delete controller;
}

void givenUpdateWhenBothStatesAreFalseThenSetIdleState(void) {
    InputProps input[] = {{false, false}};
    ControllerState expected[] = {IDLE_STATE};

    testGenerator(input, expected, IDLE_STATE);
}

void givenUpdateWhenFirstIsTrueAndSecoundIsFalseThenSetTriggeredAState(void) {
    InputProps input[] = {{true, false}};
    ControllerState expected[] = {TRIGGERED_A_STATE};

    testGenerator(input, expected, IDLE_STATE);
}

void givenUpdateWhenFirstIsFalseAndSecoundIsTrueThenSetTriggeredBState(void) {
    InputProps input[] = {{false, true}};
    ControllerState expected[] = {TRIGGERED_B_STATE};

    testGenerator(input, expected, IDLE_STATE);
}

void givenUpdateWhenBothStatesAreTrueThenSetIdleState(void) {
    InputProps input[] = {{true, true}};
    ControllerState expected[] = {IDLE_STATE};

    testGenerator(input, expected, IDLE_STATE);
}

//////////////////////////////////

void givenUpdateWhenBothStatesAreTrueAndWasTriggeredAThenSetFreedAState(void) { // add new animation
    InputProps input[] = {{true, false}, {true, true}};
    ControllerState expected[] = {TRIGGERED_A_STATE, FREED_A_STATE};

    testGenerator(input, expected, IDLE_STATE);
}

void givenUpdateWhenBothStatesAreTrueAndWasTriggeredBThenSetFreedBState(void) { // add new animation
    InputProps input[] = {{false, true}, {true, true}};
    ControllerState expected[] = {TRIGGERED_B_STATE, FREED_B_STATE};

    testGenerator(input, expected, IDLE_STATE);
}

void givenUpdateWhenBothStatesAreFalseAndWasTriggeredAThenSetFreedAState(void) {
    InputProps input[] = {{true, false}, {false, false}};
    ControllerState expected[] = {TRIGGERED_A_STATE, FREED_A_STATE};

    testGenerator(input, expected, IDLE_STATE);
}

void givenUpdateWhenBothStatesAreFalseAndWasTriggeredBThenSetFreedBState(void) {
    InputProps input[] = {{false, true}, {false, false}};
    ControllerState expected[] = {TRIGGERED_B_STATE, FREED_B_STATE};

    testGenerator(input, expected, IDLE_STATE);
}

//////////////////////////////////

void givenUpdateWhenFirstIsTrueAndSecoundIsFalseAndWasFreedAThenSetTriggeredAState(void) {
    InputProps input[] = {{true, false}, {false, false}, {true, false}};
    ControllerState expected[] = {TRIGGERED_A_STATE, FREED_A_STATE, TRIGGERED_A_STATE};

    testGenerator(input, expected, IDLE_STATE);
}

void givenUpdateWhenFirstIsFalseAndSecoundIsTrueAndWasFreedAThenSetTriggeredBState(void) {
    InputProps input[] = {{true, false}, {false, false}, {false, true}};
    ControllerState expected[] = {TRIGGERED_A_STATE, FREED_A_STATE, TRIGGERED_B_STATE};

    testGenerator(input, expected, IDLE_STATE);
}

void givenUpdateWhenFirstIsFalseAndSecoundIsTrueAndWasFreedBThenSetTriggeredBState(void) {
    InputProps input[] = {{false, true}, {false, false}, {false, true}};
    ControllerState expected[] = {TRIGGERED_B_STATE, FREED_B_STATE, TRIGGERED_B_STATE};

    testGenerator(input, expected, IDLE_STATE);
}

void givenUpdateWhenFirstIsTrueAndSecoundIsFalseAndWasFreedBThenSetTriggeredAState(void) {
    InputProps input[] = {{false, true}, {false, false}, {true, false}};
    ControllerState expected[] = {TRIGGERED_B_STATE, FREED_B_STATE, TRIGGERED_A_STATE};

    testGenerator(input, expected, TRIGGERED_B_STATE);
}

//////////////////////////////////

void givenUpdateWhenBothAreFalseAndWasActiveThenSetFreedAState(void) {
    InputProps input[] = {{false, false}};
    ControllerState expected[] = {FREED_A_STATE};

    testGenerator(input, expected, ACTIVE_STATE);
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
    UNITY_END();

    return 0;
}