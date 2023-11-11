#pragma once

#include "citem.h"

class CPhoenixFeather : public CItem
{
public:
    CPhoenixFeather();

    virtual void deathEffect() override;
};
