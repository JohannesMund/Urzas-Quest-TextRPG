#pragma once

#include "cenemy.h"

class CNpc;
class CNpcEnemy : public CEnemy
{
public:
    CNpcEnemy(const CNpc* npc);
    virtual void postBattle() override;

protected:
    virtual std::string translatorModuleName() const override;
};