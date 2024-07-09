#pragma once

#include "cenemyhorde.h"

class CCannibalHorde : public CEnemyHorde
{
public:
    CCannibalHorde();

    virtual void spoilsOfWar() const override;
    virtual void postBattle() override;
};
