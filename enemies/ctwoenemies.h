#pragma once

#include "cenemy.h"

#include <string>

class CTwoEnemies : public CEnemy
{
public:
    enum class EWho
    {
        eEnemy1,
        eEnemy2
    };

    CTwoEnemies(std::string name1, std::string name2);

    virtual void preBattleAction() override;
    virtual void battleAction(bool& endRound) override;
    virtual void postBattleAction() override;

    virtual void passiveBattleAction(EWho) = 0;

    virtual std::string name() const override;

protected:
    unsigned int _hp1;
    unsigned int _hp2;

    std::string _name1;
    std::string _name2;

    EWho _currentTarget = EWho::eEnemy1;
    int _lastHp;
};
