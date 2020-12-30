#include "Control.h"
#include "TacticSwitch.h"

class TacticSwitchController : public Control {
    public:
    TacticSwitchController(uint8_t startPinNumber, uint8_t endPinNumber);
    ~TacticSwitchController();

    void update();

    private:
    TacticSwitch *switchA, *switchB;
};