#pragma once

#include "ctalkinteraction.h"

class CNpc;
class CMenu;
class CGenieTalkInteraction : public CTalkInteraction
{
public:
    CGenieTalkInteraction(CNpc* npc);
    virtual void executeInteraction() override;

protected:
    virtual std::string translatorModuleName() const override;
};