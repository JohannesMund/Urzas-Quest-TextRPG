#pragma once
#include "ctask.h"

class CCapitalDungeonBossTask : public CTask
{
public:
    CCapitalDungeonBossTask(bool* bossDefeated);

    virtual void execute() override;

    virtual bool isMovable() const override;

protected:
    virtual std::string translatorModuleName() const override;

private:
    bool* _bossDefeated;
};
