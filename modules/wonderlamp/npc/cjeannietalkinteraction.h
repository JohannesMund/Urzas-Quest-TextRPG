#pragma once

#include "ctalkinteraction.h"

class CNpc;
class CMenu;
class CJeannieTalkInteraction : public CTalkInteraction
{
public:
    CJeannieTalkInteraction(CNpc* npc);
    virtual void executeInteraction() override;

protected:
    virtual std::string translatorModuleName() const override;
};