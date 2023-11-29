#pragma once

#include "cenemy.h"

#include <vector>

class CEnemyHorde : public CEnemy
{
public:
    CEnemyHorde(const unsigned int count, const unsigned int minHp, const unsigned int maxHp);

    virtual void preBattleAction() override;
    virtual void battleAction(bool& endRound) override;
    virtual void postBattleAction() override;

    virtual unsigned int damage() const override;

    virtual std::string name() const override;

private:
    void removeDeadEnemies();
    std::vector<int> _hps;
    int _lastHp;
    unsigned int _simultaneousAttacks = 5;
    unsigned int _attacks = 0;
};
