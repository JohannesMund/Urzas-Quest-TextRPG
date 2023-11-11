#pragma once

#include "cshield.h"

class CJunkShield : public CShield
{
public:
    CJunkShield();

    virtual std::string name() const override;
    virtual void battleEffect(CEnemy* enemy) override;
    virtual void battleBuff(CEnemy* enemy, bool& endRound) override;
};
