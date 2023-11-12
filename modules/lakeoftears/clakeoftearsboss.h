#pragma once

#include <cenemy.h>

class CLakeOfTearsBoss : public CEnemy
{
public:
    CLakeOfTearsBoss();

    virtual void spoilsOfWar() const override;
    virtual void preBattleAction() override;
    virtual void battleAction(bool& endRound) override;
    virtual void postBattleAction() override;

private:
    enum class EWho
    {
        eBimmelchen,
        ePimmelchen
    };

    unsigned int _hp1;
    unsigned int _hp2;

    EWho _currentTarget = EWho::eBimmelchen;
    int _lastHp;
};
