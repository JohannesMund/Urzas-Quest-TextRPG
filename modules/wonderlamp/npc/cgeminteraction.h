#pragma once

#pragma once

#include "cnpcinteraction.h"
class CNpc;
class CMenu;
class CGemInteraction : public CNpcInteraction
{
public:
    CGemInteraction(CNpc* npc);

    virtual void executeInteraction() override;
    virtual bool interactionAvailable() const override;

protected:
    virtual void makeNav(CMenu& menu) override;
    virtual std::string translatorModuleName() const override;
};