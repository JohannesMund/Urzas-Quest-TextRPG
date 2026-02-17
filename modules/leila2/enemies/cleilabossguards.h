#pragma once

#include "ctwoenemies.h"

class CLeilaBossGuards : public CTwoEnemies
{
public:
    CLeilaBossGuards();

    virtual void spoilsOfWar() const override;
    virtual void passiveBattleAction(CTwoEnemies::EWho who) override;

protected:
    virtual std::string translatorModuleName() const override;
};
