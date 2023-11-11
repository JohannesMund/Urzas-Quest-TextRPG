#pragma once

#include <cenemy.h>

class CRatFarmRat : public CEnemy
{
public:
    CRatFarmRat();

    virtual void battleAction(bool& endRound) override;
    virtual void spoilsOfWar() const override;
};
