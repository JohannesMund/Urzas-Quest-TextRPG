#pragma once

#include "cdungeon.h"

class CCapitalDungeon : public CDungeon
{
public:
    virtual void execute() override;
    virtual void loopHook() override;

private:
    void makeLeilaAvailable();
    void makeBossAvailable();
    void makeExitAvailable();

    bool _bossDefeated = false;
    bool _bossAwake = false;
    bool _leilaAvailable = false;
    bool _leilaRescued = false;
};
