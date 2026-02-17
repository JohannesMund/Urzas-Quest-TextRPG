#pragma once

#include "citem.h"

class CPhoenixFeather : public CItem
{
public:
    CPhoenixFeather();

    virtual void deathEffect() override;

protected:
    virtual std::string translatorModuleName() const override;
};
