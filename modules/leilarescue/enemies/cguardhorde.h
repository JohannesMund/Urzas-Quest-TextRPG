#pragma once

#include "cenemyhorde.h"

class CGuardHorde : public CEnemyHorde
{
public:
    CGuardHorde();

    virtual void spoilsOfWar() const override;

protected:
    virtual std::string translatorModuleName() const override;
};
