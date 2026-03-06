#pragma once

#include "cnpcinteraction.h"
#include "ressources.h"

class CTalkInteraction : public CNpcInteraction
{
public:
    CTalkInteraction(CNpc* npc, const std::string_view& objectName);

    virtual bool interactionAvailable() const override;

protected:
    virtual void makeNav(CMenu& menu) override;
};