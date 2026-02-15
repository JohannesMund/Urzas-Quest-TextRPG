#pragma once

#include "ctwoenemies.h"

class CLeilaBossOrks : public CTwoEnemies
{
public:
    CLeilaBossOrks();

    virtual void spoilsOfWar() const override;
    virtual void passiveBattleAction(CTwoEnemies::EWho who) override;

    virtual std::string name() const override;

protected:
    virtual std::string translatorModuleName() const override;
};
