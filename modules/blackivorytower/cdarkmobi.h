#pragma once

#include <cenemy.h>

class CDarkMobi : public CEnemy
{
public:
    CDarkMobi();

    virtual void spoilsOfWar() const override;
    virtual void battleAction(bool& endRound) override;
    virtual void postBattle() override;
};
