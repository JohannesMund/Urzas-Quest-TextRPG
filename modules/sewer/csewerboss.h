#pragma once

#include <cenemy.h>

class CSewerBoss : public CEnemy
{
public:
    CSewerBoss();

    virtual void spoilsOfWar() const override;
    virtual void battleAction(bool& endRound) override;
    virtual void postBattle() override;
};
