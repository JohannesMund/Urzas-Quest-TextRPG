#pragma once

#include "csupportcompanion.h"
#include "ressources.h"

class CNpc;
class CDjinnCompanion : public CSupportCompanion
{
public:
    CDjinnCompanion(const CNpc* npc);

    virtual std::string name() const override;
    virtual std::string type() const override;

    virtual void battleAction(CEnemy* enemy, bool& endRound) override;
    virtual void postBattle(CEnemy* enemy) override;
    virtual int shield(const int i) override;

    virtual void joinText() const override;
    virtual void leaveText() const override;

private:
    const CNpc* _djinn;
};