#pragma once
#include <ctwoenemies.h>

class CLaylaBoss : public CTwoEnemies
{
public:
    CLaylaBoss();

    virtual void spoilsOfWar() const override;

    virtual void passiveBattleAction(CTwoEnemies::EWho who) override;
};
