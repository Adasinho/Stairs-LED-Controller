#include "StateController.h"
#include "Timer.h"

class TacticSwitch : public StateController {
    public:
    TacticSwitch();
    ~TacticSwitch();

    void update(bool switchState);

    private:
    Timer *timer;
};