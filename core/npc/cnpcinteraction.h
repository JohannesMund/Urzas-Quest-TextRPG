#pragma once
#include "cgamestateobject.h"
#include "cmenuaction.h"

#include <nlohmann/json_fwd.hpp>

class CNpc;
class CMenu;
class CNpcInteraction : public CGameStateObject
{
public:
    CNpcInteraction(CNpc* npc, const std::string_view& objectName);
    virtual ~CNpcInteraction(){};

    bool checkNav(const CMenuAction& nav) const;
    CMenuAction nav(CMenu& menu);

    virtual void executeInteraction() = 0;
    virtual bool interactionAvailable() const = 0;

    nlohmann::json save() const override;
    virtual void load(const nlohmann::json& json) override;

protected:
    virtual std::string translatorObjectName() const override;
    virtual std::string translatorModuleName() const override;

    CNpc* _npc = nullptr;
    CMenuAction _nav;

private:
    virtual void makeNav(CMenu& menu) = 0;
};
