#pragma once

#include "ctalkinteraction.h"

class CNpc;
class CMenu;
class CKatTalkInteraction : public CTalkInteraction
{
public:
    CKatTalkInteraction(CNpc* npc);
    virtual void executeInteraction() override;

protected:
    virtual std::string translatorModuleName() const override;
};