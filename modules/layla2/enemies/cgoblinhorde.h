#pragma once

#include "cenemyhorde.h"

class CGoblinHorde : public CEnemyHorde
{
public:
    CGoblinHorde();

    virtual void spoilsOfWar() const override;
};
