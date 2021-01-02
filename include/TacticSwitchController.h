#include "Control.h"
#include "TacticSwitch.h"

class TacticSwitchController : public Control {
    public:
    TacticSwitchController();
    ~TacticSwitchController();

    void update(bool stateA, bool stateB);

    private:
    TacticSwitch *switchA, *switchB;
};