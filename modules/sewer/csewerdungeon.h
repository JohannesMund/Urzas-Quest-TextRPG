#pragma once

#include "cdungeon.h"

class CSewerDungeon : public CDungeon
{
public:
    CSewerDungeon();

    virtual void execute() override;
    virtual void loopHook() override;

private:
    bool _bossDefeated = false;
    bool _bossAwake = false;
};
