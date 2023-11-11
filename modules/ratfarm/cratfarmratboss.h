#pragma once

#include <cenemy.h>

class CRatFarmRatBoss : public CEnemy
{
public:
    CRatFarmRatBoss();

    virtual void battleAction(bool& endRound) override;
    virtual void spoilsOfWar() const override;
};
