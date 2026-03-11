#pragma once

#include "cnpcinteraction.h"

class CNpc;
class CMenu;
class CDoenerInteraction : public CNpcInteraction
{
public:
    CDoenerInteraction(CNpc* npc);
    virtual void executeInteraction() override;

    virtual bool interactionAvailable() const override;

    virtual nlohmann::json save() const override;
    virtual void load(const nlohmann::json& json) override;

protected:
    virtual void makeNav(CMenu& menu) override;

    virtual std::string translatorModuleName() const override;

private:
    bool _hadADoener = false;
};