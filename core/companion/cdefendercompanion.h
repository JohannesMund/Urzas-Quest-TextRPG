#pragma once

#include "ccompanion.h"

class CDefenderCompanion : public CCompanion
{
public:
    CDefenderCompanion();
    virtual std::string name() const override;
    virtual std::string type() const override;

    virtual void preBattle(CEnemy* enemy) override;
    virtual void battleAction(CEnemy* enemy, bool& endRound) override;
    virtual void postBattle(CEnemy* enemy) override;
    virtual int shield(const int i) override;

protected:
    virtual std::string translatorModuleName() const override;
};
