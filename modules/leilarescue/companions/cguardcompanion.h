#pragma once

#include "ccompanion.h"
#include "ressources.h"

class CGuardCompanion : public CCompanion
{
public:
    CGuardCompanion(const std::string_view& name);

    virtual std::string name() const override;
    virtual std::string type() const override;

    virtual void preBattle(CEnemy* enemy) override;
    virtual void battleAction(CEnemy* enemy, bool& endRound) override;
    virtual void postBattle(CEnemy* enemy) override;
    virtual int shield(const int i) override;

private:
    Ressources::Companion::ECompanionType _type;
    std::string _name;
};