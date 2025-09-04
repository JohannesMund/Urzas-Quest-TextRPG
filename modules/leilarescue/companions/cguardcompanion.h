#pragma once


#include "csupportcompanion.h"
#include "ressources.h"

class CGuardCompanion : public CSupportCompanion
{
public:
    CGuardCompanion(const std::string_view& name);

    virtual std::string name() const override;
    virtual std::string type() const override;

    virtual void preBattle(CEnemy* enemy) override;
    virtual void battleAction(CEnemy* enemy, bool& endRound) override;
    virtual void postBattle(CEnemy* enemy) override;
    virtual int shield(const int i) override;


    virtual void joinText() const override;
    virtual void leaveText() const override;

private:
    Ressources::Companion::ECompanionType _type;
    std::string _name;
};