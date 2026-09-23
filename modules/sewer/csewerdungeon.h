#pragma once

#include "cdungeon.h"

class CSewerDungeon : public CDungeon
{
public:
    CSewerDungeon();

    virtual void execute() override;
    virtual void loopHook() override;

private:
    virtual std::string translatorModuleName() const override;

    bool _bossDefeated = false;
    bool _bossAwake = false;
};
