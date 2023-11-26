#pragma once

#include "ctwoenemies.h"

class CLaylaBossOrks : public CTwoEnemies
{
public:
    CLaylaBossOrks();

    virtual void spoilsOfWar() const override;
    virtual void passiveBattleAction(CTwoEnemies::EWho who) override;

    virtual std::string name() const override;
};
