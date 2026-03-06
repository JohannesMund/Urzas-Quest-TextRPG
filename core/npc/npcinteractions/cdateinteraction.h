#pragma once

#include "cnpcinteraction.h"
#include "ressources.h"

class CDateInteraction : public CNpcInteraction
{
public:
    CDateInteraction(CNpc* npc);

    virtual void executeInteraction() override;
    virtual bool interactionAvailable() const override;

protected:
    virtual void makeNav(CMenu& menu) override;
};