#pragma once

#include "cfield.h"

class CInjuredPet : public CField
{
public:
    CInjuredPet();

    virtual void execute() override;

protected:
    virtual nlohmann::json save() const override;
    virtual void load(const nlohmann::json& json) override;

private:
    bool _petIsDead = false;
    virtual char getMapSymbol() const override;
};
