#pragma once

#include <ccompanion.h>

class CScaryMonsterCompanion : public CCompanion
{
public:
    CScaryMonsterCompanion();
    virtual std::string name() const override;
    virtual std::string type() const override;

    virtual void preBattle(CEnemy* enemy) override;
    virtual void battleAction(CEnemy* enemy, bool& endRound) override;
    virtual void postBattle(CEnemy* enemy) override;
    virtual int shield(const int i) override;
};
