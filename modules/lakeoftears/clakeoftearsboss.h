#pragma once

#include "ctwoenemies.h"

class CLakeOfTearsBoss : public CTwoEnemies
{
public:
    CLakeOfTearsBoss();

    virtual void spoilsOfWar() const override;

    virtual void passiveBattleAction(CTwoEnemies::EWho who) override;
};
