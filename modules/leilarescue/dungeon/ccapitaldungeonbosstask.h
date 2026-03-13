#pragma once
#include "ctask.h"

class CCapitalDungeonBossTask : public CTask
{
public:
    CCapitalDungeonBossTask(bool* bossDefeated);

    virtual void execute() override;

protected:
    virtual std::string translatorModuleName() const override;

private:
    bool* _bossDefeated;
};
