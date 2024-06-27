#pragma once
#include <ctwoenemies.h>

class CLeilaBoss : public CTwoEnemies
{
public:
    CLeilaBoss();

    virtual void spoilsOfWar() const override;

    virtual void passiveBattleAction(CTwoEnemies::EWho who) override;
};
