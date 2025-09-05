#pragma once


#include "csupportcompanion.h"
#include "ressources.h"

class CLeilaCompanion : public CSupportCompanion
{
public:
    CLeilaCompanion();

    virtual std::string name() const override;
    virtual void preBattle(CEnemy* enemy) override;
    virtual void battleAction(CEnemy* enemy, bool& endRound) override;
    virtual void postBattle(CEnemy* enemy) override;

    virtual void joinText() const override;
    virtual void leaveText() const override;


private:
};