#pragma once
#include "ctask.h"

class CCapitalDungeonBossTask : public CTask
{
public:
    CCapitalDungeonBossTask(bool* bossDefeated);

    virtual void execute() override;

private:
    bool* _bossDefeated;
};
