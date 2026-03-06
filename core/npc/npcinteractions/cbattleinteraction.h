#pragma once

#include "cnpcinteraction.h"
#include "ressources.h"

class CBattleInteraction : public CNpcInteraction
{
public:
    CBattleInteraction(CNpc* npc);

    virtual bool interactionAvailable() const override;
    virtual void executeInteraction() override;

protected:
    virtual void makeNav(CMenu& menu) override;
};