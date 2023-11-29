#pragma once

#include "cfield.h"

class CInjuredPet : public CField
{
public:
    CInjuredPet();

    virtual void execute() override;

private:
    bool _petIsDead = false;

    virtual char getMapSymbol() const override;
};
