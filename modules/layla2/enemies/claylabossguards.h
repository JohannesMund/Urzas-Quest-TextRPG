#pragma once

#include "ctwoenemies.h"

class CLaylaBossGuards : public CTwoEnemies
{
public:
    CLaylaBossGuards();

    virtual void spoilsOfWar() const override;
    virtual void passiveBattleAction(CTwoEnemies::EWho who) override;
};
