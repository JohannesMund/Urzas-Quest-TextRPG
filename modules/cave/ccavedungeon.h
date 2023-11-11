#pragma once

#include "cdungeon.h"

class CCaveBossTask;
class CCaveDungeon : public CDungeon
{
public:
    CCaveDungeon();

    virtual void execute() override;
    virtual void loopHook() override;

private:
    bool _bossAwake = false;
    bool _bossDefeated = false;
    unsigned int _moveCycle = 0;
};
