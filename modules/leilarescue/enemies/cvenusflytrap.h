#pragma once

#include <cenemy.h>

class CVenusFlyTrap : public CEnemy
{
public:
    CVenusFlyTrap();

    virtual void spoilsOfWar() const override;
    virtual void battleAction(bool& endRound) override;
};
